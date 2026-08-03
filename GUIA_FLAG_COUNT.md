# Guía: implementar la flag `--count` en vivo

> **Objetivo:** una flag `--count` que ejecute el ordenamiento y muestre **solo
> el número total de movimientos**, SIN imprimir las operaciones.
>
> Son **7 archivos** tocados y **~30 líneas** nuevas. Verificado: 30/30 semillas
> × 4 estrategias con el total exacto, todos los small-n, y sin leaks.

---

## LA IDEA (para explicarla antes de teclear)

El problema: cada operación imprime su nombre desde las funciones "crudas"
(`swap_a` hace `write(1,"sa\n",3)`). Hay que **silenciarlas** sin duplicar
código.

La solución se apoya en dos cosas que **ya existen** en el proyecto:

1. Cada operación tiene **DOS versiones**:
   - **pura** (solo mueve, NO imprime): `swap`, `push`, `rotate`, `reverse_rotate`
   - **con impresión**: `swap_a`, `pa`, `pb`, `rotate_a`, `reverse_rotate_b`...
2. Los wrappers `op_*` (que ya cuentan en `op_count[]`) llaman a las de impresión.

**El truco:** añadimos un slot extra al array `op_count[]` que actúa de
interruptor (`OP_SILENCE`). Si vale 1, los `op_*` llaman a la versión **pura**
(no imprime); si vale 0, a la de impresión. Cuentan igual en ambos casos.

Ventajas (defendible): **sin variables globales**, sin tocar el struct de datos
`t_stack`, y sin pasar parámetros nuevos — el array `op_count` ya viaja a todas
las funciones de ordenación.

**Orden de trabajo (7 pasos):**
`.h` → `flags.c` → `main.c` → `run_sort.c` (init) → `op_utils*.c` → `run_sort.c`
(salida) → `sort_simple.c`/`special_sort.c`.

---

## PASO 1 — `push_swap.h` · enum `e_op`

Añadir el interruptor al final del enum (índice 11):

```c
enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_SILENCE      // <-- NUEVO (indice 11)
};
```

---

## PASO 2 — `flags.c` · dos funciones

**2a) `get_flag_type`** — reconocer la flag (tipo 6):

```c
	if (str_equals(str, "--bench") == 0)
		return (5);
	if (str_equals(str, "--count") == 0)     // <-- NUEVO
		return (6);
	return (0);
```

**2b) `ft_init_flags`** — inicializar 6 slots en vez de 5:

```c
	i = 0;
	while (i < 6)          // <-- ANTES: i < 5
		flag_coun[i++] = 0;
```

⚠️ Si no se amplía, `flags[5]` queda con basura y podría activarse solo.

> Nota: `--count` NO entra en `has_conflict` (esa función solo mira los 4
> primeros = las estrategias). `--count` es ortogonal, como `--bench`.

---

## PASO 3 — `main.c` · función `main`

Agrandar el array de flags:

```c
	int		flag_coun[6];     // <-- ANTES: flag_coun[5]
```

> El parser guarda cada flag en `flag_coun[type - 1]`, así que `--count`
> (tipo 6) cae en **`flags[5]`**.

---

## PASO 4 — `run_sort.c` · `init_counts` y `execute_sort`

**4a) `init_counts`** — reservar 12 ints (11 operaciones + el interruptor):

```c
	op_counts = malloc(sizeof(int) * 12);    // <-- ANTES: * 11
	if (!op_counts)
		return (NULL);
	i = 0;
	while (i < 12)                            // <-- ANTES: i < 11
		op_counts[i++] = 0;
```

⚠️ **El bucle también a 12**: si se reserva 12 pero se limpian 11, `OP_SILENCE`
queda con basura y podría silenciar la salida normal sin querer.

**4b) `execute_sort`** — activar el interruptor ANTES de ordenar:

```c
	op_counts = init_counts();
	if (!op_counts)
		return (NULL);
	if (flags[5] > 0)                 // <-- NUEVO: --count activo
		op_counts[OP_SILENCE] = 1;
	if (!strategy_forced(flags) && n >= 2 && n <= 5)
		run_small_sort(a, n, op_counts);
	else
		run_strategy_sort(a, n, strategy, op_counts);
	return (op_counts);
```

> Es el punto exacto: `op_counts` acaba de crearse, `flags` ya está disponible,
> y es **antes** de correr el sort (así todas las `op_*` lo ven).

---

## PASO 5 — `op_utilsa.c` y `op_utilsb.c` · las 8 funciones `op_*`

El patrón es idéntico en las 8: **si silencio → versión pura; si no → versión
con impresión**. El contador se incrementa siempre.

**`op_utilsa.c`:**

```c
void	op_swap_a(t_stack *a, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		swap(a);
	else
		swap_a(a);
	op_count[OP_SA]++;
}

void	op_swap_b(t_stack *b, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		swap(b);
	else
		swap_b(b);
	op_count[OP_SB]++;
}

void	op_push_a(t_stack **a, t_stack **b, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		push(a, b);
	else
		pa(a, b);
	op_count[OP_PA]++;
}

void	op_push_b(t_stack **a, t_stack **b, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		push(b, a);        // <-- OJO: parametros INVERTIDOS
	else
		pb(a, b);
	op_count[OP_PB]++;
}
```

⚠️ **Trampa en `op_push_b`**: `pb(a, b)` internamente hace `push(b, a)` (empuja
de A hacia B). Al llamar a `push` directamente hay que **invertir** el orden:
`push(b, a)`. Si se pone `push(a, b)` mueve en la dirección contraria.

**`op_utilsb.c`:**

```c
void	op_rotate_a(t_stack *a, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		rotate(a);
	else
		rotate_a(a);
	op_count[OP_RA]++;
}

void	op_rotate_b(t_stack *b, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		rotate(b);
	else
		rotate_b(b);
	op_count[OP_RB]++;
}

void	op_rev_rotate_a(t_stack *a, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		reverse_rotate(a);
	else
		reverse_rotate_a(a);
	op_count[OP_RRA]++;
}

void	op_rev_rotate_b(t_stack *b, int *op_count)
{
	if (op_count[OP_SILENCE] == 1)
		reverse_rotate(b);
	else
		reverse_rotate_b(b);
	op_count[OP_RRB]++;
}
```

---

## PASO 6 — `run_sort.c` · `run_and_output` (LA SALIDA)

Aquí se imprime el total. **Clave: el total solo existe DESPUÉS de ordenar.**
`execute_sort` **devuelve** el `op_counts` ya relleno — se recoge en una
variable **local** (no hace falta pasarlo como parámetro).

```c
void	run_and_output(t_stack **a, int *flags, int count, double dis)
{
	int	*op_counts;                       // <-- NUEVA variable local

	if (count <= 1 || dis == 0.0)
	{
		if (flags[5] > 0)                 // <-- NUEVO: count -> imprime 0
		{
			ft_putnbr_fd(0, 1);
			write(1, "\n", 1);
		}
		else if (count > 1 && flags[4] > 0)
			print_bench(flags, dis, init_counts());
		return ;
	}
	if (flags[5] > 0)                     // <-- NUEVO: rama --count
	{
		op_counts = execute_sort(a, count, choose_strategy(flags, dis), flags);
		ft_putnbr_fd(total_from_counts(op_counts), 1);
		write(1, "\n", 1);
		free(op_counts);
	}
	else if (flags[4] > 0)                // <-- ANTES era "if", ahora ELSE IF
		print_bench(flags, dis, execute_sort(a, count,
				choose_strategy(flags, dis), flags));
	else
		free(execute_sort(a, count, choose_strategy(flags, dis), flags));
}
```

⚠️ **Trampa gorda**: el `if (flags[4])` del bench debe pasar a **`else if`**. Si
se deja como `if` suelto, con `--count` se ejecuta la rama count **Y ADEMÁS** el
`else` de abajo → **ordena dos veces**.

⚠️ El caso "ya ordenada / n<=1" hay que cubrirlo también, o `--count` no imprime
nada en esos casos (debe imprimir `0`).

---

## PASO 7 — `sort_simple.c` y `special_sort.c` · usar los wrappers

**Este es el paso que más se olvida.** El interruptor solo lo miran los `op_*`.
Estas dos funciones llamaban a las operaciones **crudas** (que siempre imprimen)
y contaban a mano → hay que cambiarlas a los wrappers.

**`sort_simple.c` · `rotate_to_top`:**

```c
	if (pos <= size - pos)
	{
		while (i++ < pos)
			op_rotate_a(a, op_counts);           // antes: rotate_a(a) + op_counts[OP_RA]++
	}
	else
	{
		while (i++ < size - pos)
			op_rev_rotate_a(a, op_counts);       // antes: reverse_rotate_a(a) + op_counts[OP_RRA]++
	}
```

**`sort_simple.c` · `sort_simple`:**

```c
		rotate_to_top(*a, pos, n - i, op_counts);
		op_push_b(a, b, op_counts);              // antes: pb(a,b) + op_counts[OP_PB]++
		i++;
	...
		op_push_a(a, b, op_counts);              // antes: pa(a,b) + op_counts[OP_PA]++
```

**`special_sort.c` · `special_sort`** (tres sitios):

```c
	if (count == 2)
		op_swap_a(*a, op_counts);                // antes: swap_a(*a)
	...
		op_push_b(a, b, op_counts);              // antes: pb(a,b) + op_counts[OP_PB]++
	...
	while (delay > 0 && delay--)
		op_push_a(a, b, op_counts);              // antes: pa(a,b) + op_counts[OP_PA]++
```

> Al usar el wrapper se **quita** el `op_counts[OP_XX]++` manual: lo hace el
> propio wrapper. Si se dejan los dos, **cuenta doble**.

---

## BONUS — `bench.c` · `total_from_counts` (¡el off-by-one!)

Si se amplía el array a 12, esta función **NO** debe sumar el slot 11
(`OP_SILENCE`), o el total saldría **+1** en modo count:

```c
int	total_from_counts(int *op_counts)
{
	...
	while (i < 11)          // <-- DEBE seguir en 11 (solo las 11 operaciones)
		total += op_counts[i++];
	return (total);
}
```

---

## LOS 5 ERRORES QUE COMETIMOS (para no repetirlos)

| # | Error | Síntoma |
|---|-------|---------|
| 1 | Imprimir el total DENTRO de `execute_sort`, antes de ordenar | imprime basura / 0 |
| 2 | `total_from_counts` sumando hasta `i < 12` | total = real **+1** |
| 3 | `if (flags[4])` en vez de `else if` | ordena **dos veces** |
| 4 | `sort_simple`/`special_sort` con operaciones crudas | `--simple` **imprime** las ops |
| 5 | Olvidar el `swap_a` crudo del `count == 2` | n=2 imprime `sa` y cuenta 0 |

---

## CÓMO PROBARLO (comandos rápidos)

```bash
make re
./push_swap --count 3 1 2                      # un solo numero
./push_swap --count $(seq 1 100 | tr '\n' ' ') # ordenada -> 0
ARG=$(shuf -i 1-500 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l                       # ops reales
./push_swap --count $ARG                       # debe dar el MISMO numero
./push_swap 3 1 2                              # sin flag: sigue imprimiendo ops
```

**Qué debe cumplirse:**
- `--count` imprime **un solo número**, nunca operaciones.
- Ese número **coincide exactamente** con `./push_swap $ARG | wc -l`.
- Lista ya ordenada / 1 número → `0`.
- Sin `--count`, todo sigue igual que antes (ops a stdout, bench a stderr).
- Sin leaks.
