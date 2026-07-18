# Push_swap — Diseño de algoritmos (Javi & Patri)

> Documento de diseño para implementar en C. Todo el pseudocódigo aquí ha sido
> **verificado por simulación** con datos aleatorios reales (no son cálculos "de oído").
> Los conteos de operaciones son los que dio la simulación, semilla a semilla.
> **La entrega es presencial y sin IA: hay que entender y saber defender cada línea.**

---

## 0. Mapa de las 4 estrategias obligatorias

| # | Estrategia | Clase | Método elegido | Estado |
|---|-----------|-------|----------------|--------|
| 1 | Simple      | O(n²)      | Selección por mínimos          | por implementar |
| 2 | Intermedia  | O(n√n)     | **Chunk sort (ksort)**         | diseñado ✅ |
| 3 | Compleja    | O(n log n) | **Radix binario LSD**          | diseñado ✅ |
| 4 | Adaptativa  | dispatcher | elige según índice de desorden | por rematar |

**La adaptativa NO es un algoritmo nuevo**: es un selector que, según el desorden:
- `< 0.2`  → método **O(n)** para casi-ordenados (falta diseñar)
- `0.2–0.5` → llama al **chunk**
- `≥ 0.5`  → llama al **radix**

Flags CLI: `--simple` / `--medium` / `--complex` / `--adaptive` (por defecto).
Modo `--bench` → métricas a **stderr** (las operaciones normales van a **stdout**).

---

## 1. Índice de desorden (obligatorio)

Número entre 0 y 1. Se calcula **antes de mover nada**. Cuenta pares en mal orden.

```
compute_disorder(A, n):
    mistakes = 0
    total_pairs = 0
    para i de 0 a n-1:
        para j de i+1 a n-1:
            total_pairs += 1
            si A[i] > A[j]:
                mistakes += 1
    return mistakes / total_pairs        # float en [0, 1]
```

- Ordenado total → 0. Máximo desorden (invertido) → 1.
- Es O(n²), pero se hace **una sola vez** al arrancar → no penaliza.
- Sirve para: (a) el dispatcher adaptativo, (b) el modo `--bench`.

---

## 2. psindex — normalización a rangos 1..N  (YA IMPLEMENTADO en C)

Convierte los valores originales (negativos, dispersos) en rangos **1..N** densos.
Clave para el radix: elimina el problema de los negativos en binario (los rangos
nunca son negativos).

Ejemplo: `{4, 26, 3, -54, 2, 15, -84, 12, 1}` → `{6, 9, 5, 2, 4, 8, 1, 7, 3}`

```
psindex(cadena, n):                 # devuelve puntero -> necesita malloc (vive tras el return)
    result = malloc(n * sizeof(int))
    para i de 0 a n-1:
        position = 0
        para j de 0 a n-1:
            si cadena[j] < cadena[i]:     # (j==i se salta solo: x < x es falso)
                position++
        result[i] = position + 1          # +1 => índice desde 1, no desde 0
    return result
```

Notas de la implementación real:
- `malloc` obligatorio: la función devuelve el puntero, un array local moriría al `return`.
- Sin centinela (`while cadena[i]`): se usa `n` como límite. Si no, se lee fuera del array.
- Comparar `<` (menores), no `>`. Contar menores = rango ascendente.
- No hay duplicados (los filtra el parseo antes) → cada rango es único.

---

## 3. RADIX binario LSD  (estrategia COMPLEJA, O(n log n))

### Idea
Un `int` ya ES binario en memoria — no se "convierte" nada. `(valor >> bit) & 1`
solo **lee** el bit que ya está ahí. El radix separa por bits, del menos
significativo (LSD) al más significativo, en pasadas sucesivas.

- Bit del top: `(top >> bit) & 1`
- Se trabaja sobre los **rangos** de psindex (siempre positivos → sin líos de signo).
- **Estable**: meter en B invierte, devolver con `pa` invierte otra vez → las dos
  inversiones se cancelan y se conserva el orden de las pasadas anteriores.
  (Regla: hay que vaciar B ENTERA a A en cada pasada, antes del siguiente bit.)

### Pseudocódigo
```
radix(A, n):
    nbits = 0
    while (1 << nbits) <= n: nbits++       # nº de bits para representar n
    para bit de 0 hasta nbits-1:
        tam = tamaño actual de A
        repetir tam veces:                 # una pasada = revisar cada elemento 1 vez
            b = (cima_de_A >> bit) & 1
            si b == 1: ra                  # se queda en A (va al fondo)
            si b == 0: pb                  # se va a B
        mientras B no esté vacía: pa       # devolver TODO B a A
```

### Coste real (simulado, constante para toda semilla)
| N   | operaciones |
|-----|-------------|
| 100 | **1081**    |
| 500 | **6778**    |

Coste ≈ `nbits × (n + n/2)`. Para 500: 9 bits × 750 = 6750 (cuadra con la sim).
**Independiente del desorden**: paga siempre todas las pasadas → por eso en desorden
bajo/medio no es la mejor opción, y tiene sentido el dispatcher.

---

## 4. CHUNK SORT / ksort  (estrategia INTERMEDIA, O(n√n))

La estrategia con más trabajo. Fue afinándose con simulaciones hasta bajar de los
umbrales de "excelente". Trabaja sobre los **rangos** de psindex.

### 4.1 Estructura general (UNA pasada A→B→A)
1. Se empujan **todos** los chunks a B (fase de empuje).
2. Se devuelve **todo** de B a A (fase de retorno).

### 4.2 Tamaños de chunk (decreciente + suelo)
Regla de oro base del O(n√n): tamaño y nº de chunks rondan √N. Pero el óptimo real
que encontramos es **empezar grande y decrecer, con un suelo mínimo**:
- Empezar grande vacía A pronto → beneficia a TODAS las pasadas siguientes.
- El suelo evita que quede un "resto" gigante al final (que dispararía el retorno,
  que es O(tamaño²) por mini-grupo).

Parámetros que funcionaron:
| N   | inicio (≈ log₁₀N · √N) | paso | suelo (≈ N/18–N/20) | tamaños resultantes |
|-----|------------------------|------|---------------------|---------------------|
| 100 | 20 | −2 | 6  | 20,18,16,14,12,10,8,2 |
| 500 | 60 | −5 | 25 | 60,55,50,45,40,35,30, luego 25×… , resto |

```
build_chunks(n, inicio, paso, suelo):
    chunks = []; lo = 1; size = inicio
    mientras queden números:
        si aún estamos en la parte decreciente y size > suelo:
            s = size ; size -= paso
        si no:
            s = suelo
        s = min(s, números_que_quedan)      # el último absorbe el resto
        chunks.add( (lo, lo+s-1) )
        lo += s
    return chunks
```

### 4.3 FASE DE EMPUJE (A → B)  con dirección óptima + fusión rr

Por cada chunk `[clo, chi]`, con `mid = (clo+chi)/2`:
- **mitad alta** (valor > mid) → `pb` a secas (se queda arriba en B).
- **mitad baja** (valor ≤ mid) → `pb` + mandarla al FONDO de B (`rb`).
  (Así B queda con altos arriba y bajos abajo: pre-partición en 2.)

Dos optimizaciones:
1. **Dirección por pasada**: antes de empezar el chunk, mirar (lectura gratis) si sus
   elementos están más cerca de la cima o del fondo de A, y escanear todo el chunk
   con `ra` o con `rra` según convenga (nunca alternar dentro del mismo chunk).
2. **Fusión rr** (solo en la rama `ra`): si acabas de hacer `pb` de una mitad baja
   (te queda un `rb` pendiente) y el siguiente elemento de A **no** pertenece al chunk
   (ibas a hacer `ra`), fusionas `rb + ra → rr` (1 op en vez de 2).
   OJO: si el siguiente elemento **sí** pertenece (vas a hacer otro `pb`), NO se puede
   fusionar: hay que soltar el `rb` suelto antes, o el elemento bajo se queda atrapado.

```
empuje(A, chunks):
    para cada chunk [clo,chi] (en orden: grande -> pequeño):
        mid = (clo+chi)/2
        use_ra = (posición del último objetivo desde arriba) <= (desde abajo)
        pending_rb = false
        si use_ra:
            mientras queden objetivos del chunk:
                top = cima A
                si clo <= top <= chi:                 # pertenece
                    si pending_rb: rb ; pending_rb=false   # flush antes de otro pb
                    pb
                    si top <= mid: pending_rb = true       # mitad baja -> rb diferido
                si no:                                 # no pertenece -> avanzar
                    si pending_rb: rr ; pending_rb=false   # fusiona rb+ra
                    si no: ra
            si pending_rb: rb                          # flush final del chunk
        si no (use_rra):                               # simétrico, SIN fusión rr
            mientras queden objetivos del chunk:
                bot = fondo A
                si clo <= bot <= chi:
                    pb ; si bot <= mid: rb             # mitad baja al fondo de B
                si no: rra
```

### 4.4 FASE DE RETORNO (B → A)  con vuelta corta  ← LA CLAVE del <5500

Los chunks se "pelan" de fuera hacia dentro: el último empujado tiene sus dos mitades
en las dos PUNTAS de B (alta arriba, baja abajo). Se procesa del chunk de valores más
altos al de más bajos.

**El gran ahorro**: para traer el máximo de cada mini-grupo a la cima, elegir la
**dirección más corta** (`rb` si está cerca de arriba, `rrb` si está cerca del fondo).
Antes rotábamos siempre en un solo sentido = vuelta larga. Esto solo bajó el retorno
de ~3000 a ~2000 en N=500.

```
retorno(B, chunks):
    para cada chunk (de valores más altos a más bajos):
        upper = los upper_size elementos de la CIMA de B
        extraer_desc_corto(upper)          # cada extraído -> pa
        subir los lower_size del FONDO de B a la cima con rrb
        extraer_desc_corto(lower)          # cada extraído -> pa

extraer_desc_corto(grupo):
    mientras queden elementos:
        localizar el máximo del grupo
        p = distancia desde arriba ; L = tamaño actual
        si p <= L - p: rb  × p             # vuelta corta por arriba
        si no:         rrb × (L - p)       # vuelta corta por abajo
        pa                                 # sacar el máximo a A
```

### 4.5 Coste real (simulado, combo empuje-rr + retorno-corto)
| N   | empuje | retorno | TOTAL (media 5 semillas) | umbral excelente |
|-----|--------|---------|--------------------------|------------------|
| 100 | ~365   | ~255    | **619**                  | < 700 ✅ |
| 500 | ~3280  | ~2000   | **5280**                 | < 5500 ✅ |

### 4.6 Evolución de la optimización (para el README / defensa)
| Versión | N=500 |
|---------|-------|
| Chunk de tamaño fijo (22) | ~7750 |
| + decreciente con suelo    | ~6300 |
| + dirección óptima empuje  | ~6300 |
| + **vuelta corta retorno** | ~5350 |
| + **fusión rr empuje**     | **~5280** |

Descubrimiento defendible: **la intermedia (chunk) supera a la compleja (radix)**
en 100 y 500, PESE a tener peor clase teórica — porque a estos tamaños pesa más la
constante que el exponente (`log₂500≈9` vs `√500≈22` no están tan lejos, y afinamos
mucho la constante del chunk).

### 4.7 Comportamiento del chunk según el índice de desorden (N=500)

Barrido simulado (media 3 semillas por punto). Listas generadas partiendo de la
invertida y reduciendo inversiones hasta el desorden objetivo. Radix constante (6778).

| Desorden | chunk (medio) | radix |
|----------|---------------|-------|
| 0.10 | 3816 | 6778 |
| 0.20 | 4164 | 6778 |
| 0.30 | 4236 | 6778 |
| 0.40 | 4344 | 6778 |
| 0.50 | 4550 | 6778 |
| 0.60 | 4761 | 6778 |
| 0.70 | 4673 | 6778 |
| 0.80 | 4768 | 6778 |
| 0.90 | 4672 | 6778 |
| 0.99 | 3748 | 6778 |
| 1.00 | **1518** | 6778 |
| **~0.5 ALEATORIO PURO** | **5278** | 6778 |

**Tres conclusiones (clave para el README y la defensa):**

1. **El chunk gana al radix en TODO el rango de desorden**, incluso en su peor caso
   (aleatorio puro, 5278 < 6778).

2. **La curva es una "joroba", no crece**: el coste sube hasta ~0.6-0.8 y luego BAJA.
   La lista invertida del todo (desorden 1.0) es el caso MÁS FÁCIL (1518), no el más
   difícil — porque está muy estructurada (los valores de cada chunk van en bloque).

3. **El índice de desorden NO determina el coste por sí solo — la ESTRUCTURA importa
   más.** El `0.5` construido da 4550, pero el `0.5` aleatorio puro da 5278. Mismo
   índice, coste muy distinto. El índice es un resumen "con pérdida": dice cuántos
   pares están mal, no cómo se distribuyen. El peor caso real del chunk es el
   **aleatorio uniforme** (~5278), que es justo lo que usa el evaluador (`shuf`).

### 4.8 Implicación para la ADAPTATIVA (decisión de diseño a justificar)

Como el chunk gana al radix en todo el rango, la adaptativa "óptima en operaciones"
usaría siempre el chunk. PERO el subject OBLIGA a usar O(n log n) (radix) en
desorden ≥ 0.5. El caso de evaluación (500 aleatorios con `shuf`) cae en ~0.5:
- Si la adaptativa lo enruta a **radix** (cumpliendo el mandato): 6778 → aprueba y es
  "bueno" (<8000), pero NO llega a "excelente" (<5500).
- Si lo enrutara al **chunk**: 5278 → excelente, pero incumple el mandato de clase.

Aprobar está asegurado en cualquier caso (radix 6778 << 12000). Solo se pierde el
"excelente" del caso aleatorio de la adaptativa. **Esto hay que decidirlo y
justificarlo en el README** (respetar el mandato de complejidad del subject vs.
minimizar operaciones). Nota: forzando `--medium` (chunk) sí se saca el excelente.

---

## 5. SIMPLE — selección por mínimos  (estrategia O(n²), POR IMPLEMENTAR)

La más fácil de defender. Solo tiene que **ordenar bien** (no necesita pasar umbrales).

```
simple(A, n):
    repetir n veces:
        encontrar el mínimo que queda en A
        llevarlo a la cima (ra o rra, la dirección más corta)
        pb
    repetir n veces:
        pa                    # vuelven; quedan ascendentes, el 1 en la cima
```
O(n²) por la búsqueda del mínimo en cada vuelta.

---

## 6. ADAPTATIVA — dispatcher  (POR REMATAR)

```
adaptativa(A, n):
    d = compute_disorder(A, n)
    si d < 0.2:   metodo_casi_ordenado(A, n)     # O(n)  -> POR DISEÑAR
    si 0.2 <= d < 0.5:  chunk(A, n)              # O(n√n)
    si d >= 0.5:  radix(A, n)                     # O(n log n)
```

Pendiente: diseñar el **método O(n) para desorden bajo** (casi-ordenado). Idea a
explorar: con pocos pares mal ordenados, unos pocos movimientos dirigidos
(rotaciones + swaps puntuales) bastan; el reto es garantizar que sea O(n) de verdad.

Pendiente también: **justificar los umbrales 0.2 y 0.5** con datos (medir dónde cada
método empieza a ganar al otro) → va en el README obligatorio.

---

## 7. Las 11 operaciones (referencia)

| Familia | Ops | Qué hacen |
|---------|-----|-----------|
| swap    | `sa` `sb` `ss` | intercambian los 2 de arriba de una MISMA pila |
| push    | `pa` `pb`      | mueven el de arriba de una pila a la OTRA |
| rotate  | `ra` `rb` `rr` | el primero pasa al final (arriba→abajo) |
| r.rotate| `rra` `rrb` `rrr` | el último pasa al primero (abajo→arriba) |

Las "dobles" (`ss`/`rr`/`rrr`) actúan sobre las 2 pilas en 1 sola operación → solo
usarlas cuando la coincidencia es NATURAL (si no, mueves una pila sin motivo).
Cada operación imprime su nombre en stdout (la salida ES la lista de operaciones);
en el `checker` no se imprime, solo se aplica → parámetro tipo `print` para reutilizar.

---

## 8. Recordatorios del subject (no olvidar)
- Sin argumentos → NO imprimir nada, salir limpio (≠ Error).
- Argumentos inválidos (no-int, overflow int, duplicados) → `Error\n` a **stderr**.
- Validar ANTES de convertir (ft_atoi no "falla": `"12abc"` daría 12 sin avisar).
- Duplicados: comparar sobre los enteros ya convertidos, no sobre el texto.
- Funciones permitidas: `read, write, malloc, free, exit` + `ft_printf`/equivalentes. libft OK.
- Sin variables globales. Makefile sin relink, con `$(NAME) all clean fclean re` (+`bonus`).
- README: 1ª línea en cursiva, secciones Descripción/Instrucciones/Recursos(+uso IA),
  justificación de algoritmos y umbrales, y **contribución de cada persona**.
- Bonus = `checker` (solo se evalúa si el mandatory pasa TODOS los umbrales).

---

## 9. Orden de trabajo sugerido
1. Parseo (juntos): argv → tokens → validar → int → duplicados → lista A.
2. psindex (hecho) + las 11 operaciones + `compute_disorder`.
3. Simple (rápida de hacer, da un algoritmo funcional ya).
4. Radix (sobre rangos).
5. Chunk (empuje + retorno con las 2 optimizaciones).
6. Método O(n) casi-ordenado + dispatcher adaptativo.
7. `--bench`, flags CLI, checker (bonus), README.
