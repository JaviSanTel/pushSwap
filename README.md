*Este proyecto ha sido creado como parte del currículo de 42 por javiesan, plopez-l.*

# push_swap

## Descripción

`push_swap` ordena una pila de números enteros en orden ascendente usando
**únicamente dos pilas** (`a` y `b`) y un conjunto limitado de operaciones,
mostrando por pantalla la secuencia de instrucciones necesaria para ordenarla.

El objetivo del proyecto es explorar la **complejidad algorítmica** de una forma
muy concreta: la complejidad se mide en el **número de operaciones de push_swap**
que el programa produce, no en el coste teórico de un algoritmo clásico sobre
arrays.

Esta implementación integra **tres algoritmos de ordenación** de clases de
complejidad distintas, más una **estrategia adaptativa** que no ordena por sí
misma, sino que actúa como **selector**: calcula el desorden de la entrada y
decide en tiempo de ejecución cuál de los tres algoritmos conviene usar.

## Instrucciones

**Compilación** (primero se compila la libft incluida y después el proyecto):

```bash
make        # genera el ejecutable push_swap
make clean  # elimina los ficheros objeto (.o)
make fclean # elimina los .o, la libft.a y el binario
make re     # fclean + make
```

**Ejecución:**

```bash
./push_swap 3 1 5 2 4          # enteros como argumentos separados
./push_swap "3 1 5 2 4"        # o como una única cadena entrecomillada
./push_swap --complex $ARG     # forzando una estrategia concreta
./push_swap --bench $ARG       # métricas por la salida de error
```

**Selector de estrategia** (opcional; por defecto se usa `--adaptive`):

| Flag | Estrategia | Clase de complejidad |
|------|------------|----------------------|
| `--simple`   | Ordenación por selección   | O(n²) |
| `--medium`   | Ordenación por chunks      | O(n√n) |
| `--complex`  | Radix binario (LSD)        | O(n·log n) |
| `--adaptive` | Selector (por defecto)     | según el desorden |
| `--bench`    | Métricas de benchmark      | — |

Comportamiento:

- Sin argumentos, el programa no muestra nada y devuelve el control.
- Ante una entrada inválida (valores no enteros, fuera del rango de `int` o
  duplicados) muestra `Error` por la **salida de error**.
- Si la pila ya está ordenada, no muestra nada (0 operaciones).
- Las operaciones se escriben en la **salida estándar**; las métricas del modo
  benchmark van a la **salida de error**.

## Preprocesado común: normalización a rangos

Antes de ejecutar cualquier estrategia, la entrada se normaliza a **rangos
`1..n`** (`psindex`): cada valor se sustituye por la posición que ocupa en el
orden final. Esto es clave porque:

- Elimina los números negativos y los problemas de desbordamiento de `int` en el
  **radix** (los bits de un rango positivo son triviales de leer, y el número de
  bits necesarios es exactamente el de `n`).
- Convierte los límites de cada chunk en rangos de valores contiguos y sencillos
  para la **ordenación por chunks**.
- Ordenar los rangos equivale a ordenar los valores originales, ya que los
  rangos conservan el orden relativo.

## Los tres algoritmos (justificación)

### 1. Simple — O(n²)

Ordenación por selección del mínimo: se busca repetidamente el valor más pequeño
que queda, se lleva a la cima con la rotación más corta y se empuja a `b`;
después se devuelve todo a `a`. Es O(n²) por la búsqueda lineal del mínimo en
cada vuelta. Solo necesita ordenar **correctamente**: es la estrategia de
respaldo y la más sencilla de razonar.

### 2. Intermedio — O(n√n): ordenación por chunks

Los valores se reparten en chunks cuyo tamaño está anclado a **√n**. Todo el
razonamiento se verificó mediante simulación:

- **Los tamaños son decrecientes con un suelo**: empiezan en ~`3·√n` y bajan con
  un paso fijo hasta un suelo de ~`√n`. Empezar con chunks grandes vacía `a`
  pronto, lo que beneficia a todas las pasadas siguientes; el suelo evita que
  quede un chunk enorme al final, cuyo coste de retorno sería cuadrático
  respecto a su tamaño. Tanto el número de chunks como sus tamaños se mantienen
  en Θ(√n), que es lo que fija la clase en **O(n√n)**.
- **Fase de empuje**: cada chunk se parte por su punto medio; la mitad alta se
  empuja directamente a la cima de `b` y la mitad baja se empuja y se manda al
  fondo (`pb` + `rb`). Así `b` queda pre-particionada.
- **Fase de retorno**: se localiza el mayor valor que queda en `b` y se lleva a
  la cima usando **la dirección de rotación más corta** (`rb` si está cerca de la
  cima, `rrb` si está cerca del fondo), y después `pa`. Elegir la dirección más
  corta es, con diferencia, la mayor optimización del retorno.

### 3. Complejo — O(n·log n): radix binario (LSD)

Trabaja sobre los rangos positivos. Por cada bit, del menos al más
significativo, una pasada completa manda a `b` los elementos con ese bit a `0`
(`pb`) y mantiene en `a` los que lo tienen a `1` (`ra`); después se devuelve
todo `b` a `a` (`pa`).

- Un bit se lee directamente con `(valor >> bit) & 1`: un `int` **ya está en
  binario** en memoria, no se convierte nada.
- El número de pasadas es `⌈log₂ n⌉`, calculado contando cuántas potencias de
  dos caben por debajo de `n`.
- **Estabilidad**: empujar a `b` invierte el orden y devolverlo lo invierte otra
  vez, de modo que las dos inversiones se cancelan y se conserva el orden
  conseguido por los bits anteriores. Esto solo se cumple si se vacía **toda**
  `b` en cada pasada.
- Su coste es prácticamente **independiente del desorden inicial** (siempre
  ejecuta todas las pasadas), lo que lo convierte en la opción robusta cuando la
  entrada está muy desordenada.

## La estrategia adaptativa (el selector)

No es un cuarto algoritmo de ordenación: es la estrategia que el programa usa
por defecto y que **decide cuál de los tres anteriores ejecutar**. Calcula el
índice de desorden de la entrada y enruta según su valor:

| Desorden | Régimen | Algoritmo elegido |
|----------|---------|-------------------|
| ya ordenada | — | ninguno (0 operaciones) |
| `< 0.2` | bajo | simple — O(n²) |
| `0.2 – 0.5` | medio | chunks — O(n√n) |
| `≥ 0.5` | alto | radix — O(n·log n) |

La idea es aumentar la potencia algorítmica a medida que la entrada se complica:
una lista casi ordenada apenas necesita trabajo, mientras que una completamente
revuelta no tiene estructura que aprovechar y conviene resolverla con el
algoritmo que mejor escala asintóticamente.

## Índice de desorden

Es un número entre `0` y `1` que mide lo lejos que está la pila de estar
ordenada, y se calcula **antes de hacer ningún movimiento**. Recorre todos los
pares `(i, j)` con `i < j`, cuenta cuántos están en mal orden (`a[i] > a[j]`) y
divide entre el número total de pares, `n·(n-1)/2`. Una lista ordenada da `0`;
una completamente invertida da `1`.

Lo usan tanto el selector adaptativo como el modo `--bench`, que lo muestra en
forma de porcentaje.

## Justificación de los umbrales

Los umbrales (`0.2` y `0.5`) siguen los objetivos de complejidad que exige el
enunciado para cada régimen. Dos observaciones empíricas obtenidas por
simulación condicionaron el diseño:

- El coste de la ordenación por chunks **no crece de forma monótona** con el
  índice de desorden: una lista completamente invertida es en realidad su caso
  *más fácil* (tiene mucha estructura), mientras que una entrada aleatoria
  uniforme (desorden ≈ 0.5) es su *peor caso*, que es justamente el que se usa
  en la evaluación.
- El índice de desorden es un resumen **con pérdida de información**: dos listas
  con el mismo índice pero distinta estructura pueden costar muy diferente. Es
  una buena señal para enrutar, pero no un predictor exacto del coste.

En los tamaños de evaluación, el algoritmo intermedio (chunks) produce en
realidad menos operaciones que el complejo (radix), porque con n ≤ 500 pesan más
las constantes que el exponente (`log₂ 500 ≈ 9` frente a `√500 ≈ 22`). El punto
de cruce en el que el O(n·log n) del radix supera al O(n√n) de los chunks está
en torno a **n ≈ 1000–1500**; a partir de ahí el radix escala visiblemente mejor
(de n = 500 a n = 5000 el radix multiplica sus operaciones por ~15 mientras que
los chunks lo hacen por ~33). Aun así, el selector adaptativo enruta el desorden
alto al radix para respetar el requisito de clase de complejidad del enunciado,
lo que garantiza un margen cómodo con cualquier tamaño de entrada.

## Rendimiento

Número de operaciones medido con entradas aleatorias (verificado con el checker
y sin fugas de memoria):

| n | 100 | 500 |
|---|-----|-----|
| radix  | 1081 | 6778 |
| chunks | ~620 | ~5500 |
| umbrales | supera <2000 / bueno <1500 / **excelente <700** | supera <12000 / bueno <8000 / **excelente <5500** |

## Recursos

- Enunciado de Push_swap (versión propia del campus, v1.0).
- Radix sort (LSD) y ordenación por selección/inserción — referencias clásicas
  de algoritmia.
- Distancia de Kendall-tau / conteo de inversiones — para el índice de desorden.
- **Uso de IA**: se ha utilizado un asistente de IA como *tutor y herramienta de
  verificación*, nunca como generador de código. En concreto, se usó para (a)
  explicar conceptos (operaciones a nivel de bits, estabilidad del radix, clases
  de complejidad), (b) **simular y medir** los diseños algorítmicos en Python
  antes de implementarlos en C (esquemas de tamaño de chunk, barridos del índice
  de desorden, el punto de cruce entre chunks y radix), y (c) revisar nuestro
  propio código C en busca de errores, fugas de memoria (AddressSanitizer) y
  fallos de corrección, reproduciendo las operaciones generadas. Todos los
  algoritmos fueron **diseñados e implementados por nosotros**; la IA no escribió
  el código entregado y podemos explicar y defender cada línea.

## Contribuciones

Este proyecto ha sido realizado por dos estudiantes trabajando conjuntamente;
ambos comprenden y pueden defender la totalidad del código.

- **javiesan** — Diseño e implementación de los algoritmos: los núcleos de
  ordenación (radix O(n·log n) y chunks O(n√n)), la normalización a rangos
  (`psindex`), el índice de desorden, y el diseño y ajuste del esquema de
  tamaños de chunk (simulado y medido).
- **plopez-l** — Infraestructura: análisis y validación de argumentos, la
  estructura de las pilas y las once operaciones, el selector de estrategia, el
  modo benchmark, el tratamiento de los casos pequeños y los casos límite, la
  gestión de errores y la integración.
