# Push_Swap

*This project was created as part of the 42 curriculum by [valmoral], [kramarat].*

## Description

Push_Swap is an algorithmic project that requires sorting data in a stack using a limited set of instructions. The goal is to calculate and display the shortest sequence of operations to sort a list of integers in ascending order, using only two stacks (a and b) and specific operations like swap, push, rotate, and reverse rotate.

The project explores algorithmic complexity (Big-O) in a practical way, implementing multiple sorting strategies to handle different levels of disorder in the input data. The entire codebase is fully **Norminette compliant** (42 school style enforcer).

---

## Project Structure

The source is deliberately split into small, focused files — each with at most 5 functions — as required by Norminette.

| File | Responsibility |
|---|---|
| `push_swap.c` | Entry point: parse → sort → free |
| `parsing.c` | CLI argument parsing, validation, duplicate detection |
| `bench.c` | Benchmark output to stderr (`--bench` flag) |
| `stack_utils.c` | Stack primitives: size, last node, add node, free |
| `aux_push.c` | `push`, `pa`, `pb` operations |
| `aux_swap.c` | `swap`, `sa`, `sb`, `ss` operations |
| `aux_rotate.c` | `rotate`, `ra`, `rb`, `rr` operations |
| `aux_reverse_rotate.c` | `reverse_rotate`, `rra`, `rrb`, `rrr` operations |
| `sorting.c` | Disorder metric + adaptive strategy dispatcher |
| `sorting_common.c` | `is_sorted_stack`, `sort_small_stack` |
| `sorting_simple.c` | Selection-style O(n²) sort |
| `sorting_rotate.c` | Rotate helpers: find min/max position, rotate to top |
| `sorting_index.c` | Rank assignment and insertion-position finder |
| `sorting_insertion.c` | Insertion-based O(n²) sort |
| `sorting_medium.c` | Chunk-based O(n√n) sort |
| `sorting_complex.c` | Radix O(n log n) sort |
| `libft/` | Bundled libft used for `ft_split`, `ft_strlen`, `ft_memset`, etc. |

---

## Instructions

### Compilation
```
make
```
Builds `libft` first, then `push_swap`, with `-Wall -Werror -Wextra`.

### Execution
```
./push_swap [options] <numbers>
```

Available options:

| Flag | Behaviour |
|---|---|
| *(none)* | Defaults to adaptive strategy |
| `--simple` | Forces O(n²) selection sort |
| `--insertion` | Forces O(n²) insertion sort |
| `--medium` | Forces O(n√n) chunk sort |
| `--complex` | Forces O(n log n) radix sort |
| `--adaptive` | Auto-selects based on size + disorder (default) |
| `--bench` | Prints performance metrics to stderr |

Examples:
```
./push_swap 3 2 1 4
./push_swap --bench --adaptive 5 4 3 2 1
```

If no arguments are provided, the program does nothing. On error (invalid input, duplicates, overflow), it prints `Error` to stderr and exits.

### Benchmark Output Format

With `--bench`, the program writes to stderr:
```
Disorder:  0.80
Strategy:  Adaptive -> Complex O(n log n)
Total ops: 3241
  sa=0 sb=0 ss=0 pa=500 pb=500 ra=712 rb=604 rr=0 rra=461 rrb=464 rrr=0
```

- **Disorder** — fraction of inverted pairs in [0..1]. 0 = already sorted, 1 = fully reversed.
- **Strategy** — which algorithm ran. If adaptive, shows the chosen concrete strategy.
- **Total ops** — sum of all stack operations emitted.

### Testing with Checker
```
./push_swap <args> | ./checker_linux <args>
```
Should print `OK` for any valid sorted output.

---

## Showing Runtime Strategy Selection (Evaluator Demo)

### Step 1 — Build
```
make
```

### Step 2 — Force each strategy manually and verify

```
./push_swap --simple 4 3 2 1 | ./checker_linux 4 3 2 1
./push_swap --insertion 5 1 4 2 3 | ./checker_linux 5 1 4 2 3
./push_swap --medium 8 3 6 1 9 2 5 4 7 | ./checker_linux 8 3 6 1 9 2 5 4 7
./push_swap --complex 8 3 6 1 9 2 5 4 7 | ./checker_linux 8 3 6 1 9 2 5 4 7
```

All should print `OK`.

### Step 3 — Show adaptive selection at runtime

```bash
# Nearly sorted — expect Simple
./push_swap --adaptive --bench 1 2 3 5 4

# Small, moderate disorder — expect Insertion
./push_swap --adaptive --bench 5 1 4 2 3

# Medium input — expect Medium
./push_swap --adaptive --bench 8 3 6 1 9 2 5 4 7

# Large, high disorder — expect Complex
nums=($(shuf -i 1-200 -n 200)) && ./push_swap --adaptive --bench "${nums[@]}" >/dev/null
```

The benchmark line will show which strategy was actually selected, e.g.:
```
Strategy:  Adaptive -> Simple O(n^2)
Strategy:  Adaptive -> Insertion O(n^2)
Strategy:  Adaptive -> Medium O(n √n)
Strategy:  Adaptive -> Complex O(n log n)
```

---

## Implemented Algorithms

### How the Adaptive Selector Works

Before sorting, the program computes a **disorder score** for stack A:

> disorder = (number of inverted pairs) / (total possible pairs)

A value of `0.0` means fully sorted; `1.0` means fully reversed. This is calculated in O(n²) and used to pick the cheapest strategy for the actual input rather than always running the heaviest one.

**Selection thresholds** (in `sorting.c`):

| Condition | Strategy chosen |
|---|---|
| size ≤ 5 **or** disorder < 0.12 | Simple O(n²) |
| size ≤ 32 **or** disorder < 0.35 | Insertion O(n²) |
| size ≤ 150 **or** disorder < 0.65 | Medium O(n√n) |
| everything else | Complex O(n log n) |

---

### Simple Strategy — O(n²) — `sorting_simple.c`

**How it works:** Repeatedly finds the minimum value in stack A, rotates it to the top using the shortest path (forward or reverse), and pushes it to B. Once all values are in B (descending), pulls them all back to A.

**When adaptive picks it:** Stack has ≤ 5 elements, or disorder < 0.12 (nearly sorted).

**Why:** Selection by min-finding is the cheapest possible approach when there's almost nothing to move. No overhead from index calculation or chunking.

---

### Insertion Strategy — O(n²) — `sorting_insertion.c` + `sorting_index.c`

**How it works:** Keeps 3 elements in A and sorts them with `sort_three`. Pushes everything else to B. Then reinserts each element from B into its correct position in A by rotating A to the target slot before `pa`.

**When adaptive picks it:** Stack has ≤ 32 elements, or disorder < 0.35.

**Why:** Targeting each element's exact insertion position beats chunk overhead at this scale. The per-element rotation cost averages less than the chunk setup cost.

---

### Medium Strategy — O(n√n) — `sorting_medium.c`

**How it works:** Assigns a normalized rank (0..n-1) to every node. Pushes values to B in windows of size √n (e.g. window 0 covers ranks 0..√n-1). Rebuilds A by pulling the maximum from B repeatedly.

**When adaptive picks it:** Stack has ≤ 150 elements, or disorder < 0.65.

**Why:** The chunk approach avoids full quadratic cost by grouping nearby values. Typical operation count is proportional to n × √n, making it practical for medium lists where radix setup is overkill.

---

### Complex Strategy — O(n log n) — `sorting_complex.c`

**How it works:** Assigns ranks (0..n-1) to normalise values. Sorts by each binary bit of the rank from least to most significant. In each pass: nodes whose current bit is 0 are pushed to B; nodes whose bit is 1 stay in A; then all of B is pulled back. After log₂(n) passes, A is sorted.

**When adaptive picks it:** Stack has > 150 elements and disorder ≥ 0.65.

**Why:** Radix on normalised indexes gives guaranteed O(n log n) and scales well for any large, chaotic input regardless of value distribution.

---

## Local Utility Dependency

The project now uses the bundled `libft/` directory again. Parser tokenisation, string length, memory helpers, and other shared utilities come from the library instead of root-level replacements.

---

## Resources

- [Big-O Notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Stack Data Structure](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))
- [Radix Sort](https://en.wikipedia.org/wiki/Radix_sort)
- [42 Subject PDF](es.subject%20(1).pdf)

---

## Contributions
- **valmoral**: Stack operations, main logic.
- **kramarat**: Documentation, parsing, and Norminette compliance.
- **Both**: Sorting algorithms, testing and debugging.

Both contributed significantly, understanding and explaining all code.
