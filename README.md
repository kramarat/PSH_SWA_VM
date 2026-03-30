# Push_Swap

*This project was created as part of the 42 curriculum by [valmoral], [kramarat].*

## Description

Push_Swap is an algorithmic project that requires sorting data in a stack using a limited set of instructions. The goal is to calculate and display the shortest sequence of operations to sort a list of integers in ascending order, using only two stacks (a and b) and specific operations like swap, push, rotate, and reverse rotate.

The project explores algorithmic complexity (Big-O) in a practical way, implementing multiple sorting strategies to handle different levels of disorder in the input data.

## Instructions

### Compilation
To compile the project, run:
```
make
```
This will generate the `push_swap` executable with the flags `-Wall -Werror -Wextra`.

### Execution
The program runs with a list of integers as arguments:
```
./push_swap [options] <numbers>
```

Available options:
- `--simple`: Forces the use of the O(n²) algorithm.
- `--insertion`: Forces the use of the insertion-based O(n²) algorithm.
- `--medium`: Forces the use of the O(n √n) algorithm.
- `--complex`: Forces the use of the O(n log n) algorithm.
- `--adaptive`: Uses the adaptive selector based on size and disorder (default).
- `--bench`: Shows performance metrics in stderr (disorder, strategy, total operations, and count per type).

Examples:
```
./push_swap 3 2 1 4
./push_swap --bench --adaptive 5 4 3 2 1
```

If no arguments are provided, the program does nothing. In case of error (invalid numbers, duplicates, overflow), it prints "Error" to stderr.

### Testing
To verify the output, you can use the checker provided in the 42 repository:
```
./push_swap <args> | ./checker_linux <args>
```

### Showing Runtime Strategy Selection
To demonstrate to an evaluator that the program can choose different strategies during execution depending on the input configuration:

1. Force each concrete strategy manually:
```
./push_swap --simple 4 3 2 1 | ./checker_linux 4 3 2 1
./push_swap --insertion 5 1 4 2 3 | ./checker_linux 5 1 4 2 3
./push_swap --medium 8 3 6 1 9 2 5 4 7 | ./checker_linux 8 3 6 1 9 2 5 4 7
./push_swap --complex 8 3 6 1 9 2 5 4 7 | ./checker_linux 8 3 6 1 9 2 5 4 7
```

2. Show automatic selection with adaptive mode and benchmarking:
```
./push_swap --adaptive --bench 1 2 3 5 4
./push_swap --adaptive --bench 5 1 4 2 3 6 7 8
./push_swap --adaptive --bench 8 3 6 1 9 2 5 4 7
```

In adaptive mode, the benchmark output reports the concrete strategy that was selected at runtime, for example:
- `Adaptive -> Simple O(n^2)`
- `Adaptive -> Insertion O(n^2)`
- `Adaptive -> Medium O(n √n)`
- `Adaptive -> Complex O(n log n)`

## Resources

- [Big-O Notation](https://en.wikipedia.org/wiki/Big_O_notation): To understand algorithmic complexity.
- [Stack Data Structure](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)): Basic stack concepts.
- [Sorting Algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm): References for sorting algorithms adapted to stacks.
- [42 Subject PDF](es.subject (1).pdf): The complete project statement.

### AI Usage
AI (GitHub Copilot) was used for structuring the project, including generating boilerplate code for stack operations, utility functions, and initial sorting algorithm implementations. All code was reviewed, modified, and fully understood by the developers.

## Implemented Algorithms

### Simple Strategy (O(n²))
- **Description**: Selection-style sorting adapted to Push_Swap operations.
- **How it works**: Repeatedly rotates stack a to bring the minimum value to the top, pushes it to stack b, and rebuilds the sorted result with `pa`.
- **Justification**: Efficient for very small or almost sorted inputs. O(n²) complexity in Push_Swap operations.
- **Advantages**: Simple to implement, low overhead.
- **Disadvantages**: Inefficient for large disordered lists.

### Insertion Strategy (O(n²))
- **Description**: Insertion-based sorting over a circularly ordered stack.
- **How it works**: Pushes most values to stack b, sorts the remaining core in stack a, and reinserts each value from b into its correct position by rotating a before `pa`.
- **Justification**: Distinct from the simple strategy and effective for small-to-medium inputs with moderate disorder.
- **Advantages**: Good balance between simplicity and flexibility for moderate input sizes.
- **Disadvantages**: Still quadratic in the worst case.

### Intermediate Strategy (O(n √n))
- **Description**: Chunk sorting (dividing the list into √n groups).
- **How it works**: Computes normalized indexes, pushes values from stack a to stack b in √n-sized windows, then restores them from b back to a in descending order.
- **Justification**: Improves complexity to about O(n √n) for medium-size or medium-disorder inputs.
- **Advantages**: Better than O(n²) for medium lists.
- **Disadvantages**: Requires range calculation and more intermediate operations.

### Complex Strategy (O(n log n))
- **Description**: Adaptation of radix sort (LSD - Least Significant Digit).
- **How it works**: Sorts by binary digits, using rotates and pushes to simulate the radix process on stacks.
- **Justification**: Optimal for high disorder (≥0.5), with O(n log n) complexity in operations.
- **Advantages**: Efficient for any input size.
- **Disadvantages**: More complex to implement and debug.

### Adaptive Strategy
- **Description**: Automatically selects one of the four implemented concrete sorting strategies.
- **How it works**: Calculates size and disorder at the start; for very small or almost sorted inputs it uses simple, for small/medium inputs insertion, for medium ranges chunk sorting, and for large/high-disorder inputs radix.
- **Justification**: Provides runtime selection according to input configuration while keeping the four explicit strategies available.
- **Advantages**: Flexible, no manual selection needed.
- **Disadvantages**: Initial calculation overhead.

## Contributions
- **valmoral**: Implementation of stack operations, parsing, main logic, and sorting algorithms.
- **[partner]**: [Description of contributions, e.g., testing, debugging, documentation].

Both contributed significantly, understanding and explaining all code.# PSH_SWA_VM
