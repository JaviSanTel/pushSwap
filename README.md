*Este proyecto ha sido creado como parte del currículo de 42 por javiesan, plopez-l.*

# push_swap

## Description

`push_swap` sorts a stack of integers into ascending order using **only two
stacks** (`a` and `b`) and a limited set of stack operations, printing the
sequence of instructions needed to sort the input.

The goal of the project is to explore **algorithmic complexity** in a very
concrete way: complexity is measured in the number of **push_swap operations**
produced, not in the theoretical cost of a classic array algorithm.

This implementation goes beyond a single algorithm: it integrates **four
sorting strategies of different complexity classes** plus an **adaptive
dispatcher** that selects one at runtime based on how disordered the input is.

## Instructions

**Build** (compiles the bundled libft first, then the project):

```bash
make        # builds push_swap
make bonus  # builds the checker (bonus)
make clean  # removes object files
make fclean # removes objects, libft.a and binaries
make re     # fclean + make
```

**Run:**

```bash
./push_swap 3 1 5 2 4          # integers as separate arguments
./push_swap "3 1 5 2 4"        # or as a single quoted string
./push_swap --complex $ARG     # forcing a strategy
./push_swap --bench $ARG       # metrics to stderr
```

**Strategy selector** (optional; `--adaptive` is the default):

| Flag | Strategy | Complexity class |
|------|----------|------------------|
| `--simple`   | Selection sort            | O(n²) |
| `--medium`   | Chunk sort                | O(n√n) |
| `--complex`  | Binary radix (LSD)        | O(n·log n) |
| `--adaptive` | Dispatcher (default)      | chosen by disorder |
| `--bench`    | Benchmark metrics (stderr)| — |

- With no arguments, the program prints nothing and returns control.
- On invalid input (non-integers, values out of `int` range, duplicates) it
  prints `Error` to **stderr**.
- If the stack is already sorted, it prints nothing (0 operations).
- Normal operations go to **stdout**; benchmark metrics go to **stderr**.

## Common preprocessing: rank normalization

Before any strategy runs, the input is normalized to **ranks `1..n`**
(`psindex`): each value is replaced by its position in the sorted order. This
is key because:

- It removes negative numbers and `INT` overflow concerns from the **radix**
  (bits of a positive rank are trivial to read; the number of bits is exactly
  those of `n`).
- It turns chunk boundaries into simple contiguous value ranges for the
  **chunk sort**.
- Sorting the ranks is equivalent to sorting the originals, since ranks
  preserve relative order.

## The four strategies (algorithm justification)

### 1. Simple — O(n²)

Selection by minimum extraction: repeatedly find the smallest remaining value,
bring it to the top with the shorter rotation, and push it to `b`; then bring
everything back to `a`. It is O(n²) because of the repeated linear search for
the minimum. It only needs to sort **correctly**; it is the fallback and the
easiest to reason about.

### 2. Intermediate — O(n√n): chunk sort

Values are split into chunks whose size is anchored to **√n**. All the reasoning
is verified by simulation:

- **Chunk sizes are decreasing with a floor**: they start at ~`3·√n` and shrink
  by a fixed step down to a floor of ~`√n`. Starting big empties `a` early
  (which benefits every later pass); the floor prevents a huge leftover chunk
  at the end (whose return cost is quadratic in its size). The number of chunks
  and their sizes stay Θ(√n), which is what keeps the class at **O(n√n)**.
- **Push phase**: each chunk is split by its midpoint; the upper half is pushed
  straight to the top of `b`, the lower half is pushed and sent to the bottom
  (`pb` + `rb`). This pre-partitions `b`.
- **Return phase**: repeatedly locate the largest remaining value in `b` and
  bring it to the top using the **shorter rotation direction** (`rb` if it is
  near the top, `rrb` if near the bottom), then `pa`. Choosing the shorter
  direction is the single biggest optimization of the return.

### 3. Complex — O(n·log n): binary radix (LSD)

Works on the positive ranks. For each bit, from least to most significant, one
full pass moves elements with bit `0` to `b` (`pb`) and keeps elements with bit
`1` in `a` (`ra`); then all of `b` is pushed back to `a` (`pa`).

- A bit is read directly with `(value >> bit) & 1` — an `int` is already binary,
  nothing is "converted".
- The number of passes is `⌈log₂ n⌉`, computed by counting how many powers of
  two fit under `n`.
- **Stability**: pushing to `b` reverses order and pushing back reverses it
  again, so the two inversions cancel and the order achieved by previous bits is
  preserved — provided **all** of `b` is emptied on every pass.
- Its cost is essentially **independent of the initial disorder** (it always
  performs all passes), which makes it the robust choice for highly disordered
  input.

### 4. Adaptive — dispatcher by disorder

The default strategy computes the disorder index and routes to a class that
matches the difficulty of the input:

| Disorder | Regime | Strategy used |
|----------|--------|---------------|
| already sorted | — | 0 operations |
| `< 0.2` | low  | O(n) regime |
| `0.2 – 0.5` | medium | chunk — O(n√n) |
| `≥ 0.5` | high | radix — O(n·log n) |

The idea is to increase algorithmic power as the input gets harder: a nearly
sorted list barely needs work, whereas a fully scrambled one has no structure
to exploit and is best handled by the strategy with the best asymptotic scaling.

## Disorder index

A number in `[0, 1]` measuring how far the stack is from sorted, computed
**before any move**. It counts, over every pair `(i, j)` with `i < j`, how many
are in the wrong order (`a[i] > a[j]`) and divides by the total number of pairs
`n·(n-1)/2`. Sorted → 0; fully reversed → 1.

It is used both by the adaptive dispatcher and, reported as a percentage, by the
`--bench` mode.

## Justification of the thresholds

The regimes (`0.2` and `0.5`) follow the complexity targets required by the
subject. Two empirical observations from simulation shaped the design:

- The chunk sort's cost is **not monotonic** in the disorder index: a fully
  reversed list is actually its *easiest* case (strong structure), while a
  uniformly random input (~0.5 disorder) is its *worst* case — and that random
  case is exactly what the evaluator uses.
- The disorder index is a **lossy** summary: two lists with the same index but
  different structure can cost very differently. It is a useful routing signal,
  not an exact predictor.

At the evaluation sizes the intermediate (chunk) sort actually produces fewer
operations than the complex (radix) sort, because at n ≤ 500 the constant
factors dominate over the exponent (`log₂ 500 ≈ 9` vs `√500 ≈ 22`). The
crossover where radix's O(n·log n) overtakes the chunk's O(n√n) sits around
**n ≈ 1000–1500**; from there radix scales visibly better (from n = 500 to
n = 5000 radix grows ~×15 while the chunk grows ~×33). The adaptive dispatcher
still routes high disorder to radix to honour the subject's complexity mandate,
which guarantees a comfortable pass on any input size.

## Performance

Measured operation counts on random input (checker-verified, no leaks):

| n | 100 | 500 |
|---|-----|-----|
| radix        | 1081 | 6778 |
| chunk         | ~620 | ~5500 |
| thresholds    | pass <2000 / good <1500 / **excellent <700** | pass <12000 / good <8000 / **excellent <5500** |

## Resources

- Push_swap subject (42 campus custom version, v1.0).
- Radix sort (LSD) and selection/insertion sort — classic algorithm references.
- Kendall tau distance / inversion counting — for the disorder index.
- **AI usage**: an AI assistant was used as a *tutor and verification tool*, not
  as a code generator. Concretely, it was used to (a) explain concepts
  (variadic bit operations, radix stability, complexity classes), (b)
  **simulate and benchmark** algorithm designs in Python before implementing
  them in C (chunk-size schemes, disorder sweeps, the chunk-vs-radix crossover),
  and (c) review our own C code for bugs, memory leaks (AddressSanitizer) and
  correctness by replaying the generated operations. Every algorithm was
  **designed and implemented by us**; the AI never wrote the delivered code, and
  we can explain and defend every line.

## Contributions

This project was completed by two students working together; both understand
and can defend the whole codebase.

- **javiesan** — Algorithm design and implementation: the sorting cores (radix
  O(n·log n), chunk O(n√n)), rank normalization (`psindex`), the disorder index,
  and the design/tuning of the chunk-size scheme (simulated and benchmarked).
- **plopez-l** — Infrastructure: argument parsing and validation, the stack
  structure and the eleven operations, the strategy dispatcher, benchmark mode,
  small-n and edge-case handling, error handling and integration.
