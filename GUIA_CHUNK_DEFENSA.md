# Guía del CHUNK SORT para la defensa (para Patri)

> Documento para preparar la defensa de la estrategia intermedia (`--medium`).
> Todo el pseudocódigo/código está verificado: ordena correcto, sin leaks, y da
> ~620 ops (n=100) / ~5500 ops (n=500). Archivos: `chunk.c` y `chunk_utils.c`.

---

## 1. Qué es y en qué clase encaja

El chunk sort es la estrategia **intermedia O(n√n)**. El subject la lista
literalmente como ejemplo de esa clase ("orden por chunks dividiendo en √n
chunks" y "orden basado en rangos") — y el nuestro es las dos cosas a la vez.

**Idea en una frase:** repartimos los valores en trozos ("chunks") de tamaño
~√n, los mandamos a la pila B agrupados por trozo, y luego los devolvemos a A
sacando siempre el mayor por el camino más corto.

**Por qué es O(n√n):** hay ~√n chunks, y empujar cada uno cuesta recorrer la
pila (~O(n) operaciones). √n chunks × O(n) por chunk = **O(n√n)**.

---

## 2. Preprocesado común: rangos (psindex)

Antes de ordenar, TODO se normaliza a **rangos 1..n** (cada número se sustituye
por su posición en el orden). Para el chunk esto convierte los "trozos" en
rangos de valores contiguos y sencillos (`[1..22]`, `[23..44]`...). Ordenar los
rangos = ordenar los originales (conservan el orden relativo).

---

## 3. Los tamaños de chunk (función `push_chunk`)

```c
floor = isqrt(n);          // suelo  ≈ √n
size  = 3 * floor;         // inicial ≈ 3·√n
step  = (size - floor) / 7;
```

- **Empiezan grandes y decrecen hasta un suelo de √n.** Empezar grande vacía A
  pronto (beneficia a todas las pasadas siguientes); el suelo evita que quede un
  chunk gigante al final (cuyo coste de retorno sería cuadrático).
- **El `/7`** reparte la BAJADA de tamaño (de 3√n a √n) en ~7 escalones. **NO
  divide los n números en 7 chunks.** Para n=500 salen ~15 chunks en total: unos
  8 decrecientes (66, 60, 54...) y el resto al suelo (22, 22, 22...). El 7 es un
  valor empírico calibrado por simulación (equilibrio entre pocos chunks grandes
  = retorno caro, y muchos pequeños = empuje caro).
- **Importante para la clase:** el suelo y los tamaños están anclados en **√n**
  (no en una fracción de n como n/18, que sería lineal y rompería la clase a
  O(n²)). Al anclar en √n, es O(n√n) para cualquier n.

---

## 4. FASE 1 — empuje a B (funciones `push_chunk` + `found`)

Por cada chunk `[clow, clow+csize-1]`, con `mid` = su punto medio:

```
para cada elemento del chunk (found < csize):
    t = cima de A
    si t pertenece al chunk [clow, clow+csize-1]:
        si t > mid:  op_push_b            (mitad ALTA -> arriba de B)
        si no:       op_push_b + op_rotate_b   (mitad BAJA -> al fondo de B)
        found++
    si no:
        op_rotate_a                        (no pertenece -> siguiente)
```

**El truco de las mitades:** al partir cada chunk por su punto medio y mandar la
mitad alta arriba y la baja al fondo, B queda **pre-ordenado** por trozos, lo
que abarata el retorno.

---

## 5. FASE 2 — retorno a A (función `return_global`)

**No necesita conocer los chunks.** Simplemente, mientras quede algo en B:

```
mientras B no esté vacía:
    pos = posición del MAYOR valor de B   (ft_position)
    tam = tamaño de B                     (ft_size_st)
    si el mayor está más cerca de la cima (pos <= tam - pos):
        rotar B hacia arriba (op_rotate_b) pos veces
    si no (más cerca del fondo):
        rotar B hacia abajo (op_rev_rotate_b) (tam - pos) veces
    op_push_a                              (sacar el mayor a A)
```

**La clave del rendimiento:** siempre traemos el mayor por el **lado más corto**
(rb si está cerca de arriba, rrb si está cerca del fondo). Rotar siempre en un
solo sentido daría la "vuelta larga" y duplicaría el coste del retorno. Esta es
la mayor optimización de toda la estrategia.

`ft_position` recorre B y devuelve el índice (desde 0) del valor máximo.
`ft_size_st` cuenta los nodos de B.

---

## 6. Preguntas típicas de defensa (y respuestas)

**"¿Por qué es O(n√n) y no otra clase?"**
> Hay ~√n chunks de tamaño ~√n. Empujar cada chunk cuesta O(n) (recorrer la
> pila). √n × O(n) = O(n√n). Se mide en operaciones push_swap, no del array.

**"¿Por qué el /7? ¿No rompe la complejidad?"**
> Reparte la bajada de tamaño en ~7 escalones. Es una constante fija, no depende
> de n, así que no cambia la clase. El grueso de chunks (los del suelo √n) es lo
> que domina asintóticamente. El 7 se calibró por simulación.

**"¿Cómo garantizas que el retorno sea eficiente?"**
> Traigo el máximo por el lado más corto (comparo distancia desde arriba vs
> desde abajo y elijo rb o rrb). Eso reduce a la mitad, de media, las rotaciones
> del retorno.

**"Modifícalo en vivo: ordénalo de mayor a menor."**
> En el retorno, en vez de sacar siempre el máximo, sacaría el mínimo (o
> invertiría la lógica de qué mitad va arriba/abajo en el empuje).

**"¿Cuál es el peor caso?"**
> Una lista uniformemente aleatoria (desorden ~0.5). Curiosamente, una lista
> totalmente invertida es el caso MÁS fácil (está muy estructurada).

---

## 7. Resumen de las funciones

| Función | Archivo | Qué hace |
|---|---|---|
| `isqrt` | chunk.c | raíz cuadrada entera, sin `sqrt` (bucle `i*i <= n`) |
| `push_chunk` | chunk.c | bucle exterior: calcula el rango de cada chunk |
| `found` | chunk.c | empuja los elementos de UN chunk (mitades alta/baja) |
| `return_global` | chunk.c | devuelve B→A sacando el máximo por el lado corto |
| `sort_chunk` | chunk.c | orquesta: push_chunk + return_global |
| `ft_position` | chunk_utils.c | índice del mayor valor de la pila |
| `ft_size_st` | chunk_utils.c | cuenta nodos de la pila |

Comparado con una implementación de referencia (ksort), nuestro chunk está a un
~4-10% en número de operaciones — mismo enfoque en el retorno, mecanismo propio
en el empuje.
