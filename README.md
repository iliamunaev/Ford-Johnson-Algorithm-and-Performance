# Ford-Johnson Algorithm and Performance

A comprehensive C++ implementation of the Ford-Johnson algorithm (also known as merge-insertion sort) that demonstrates performance comparisons between sequential and concurrent execution using different container types.

## Overview

The Ford-Johnson algorithm is an sorting algorithm that combines the benefits of merge sort and insertion sort. This implementation provides a performance analysis tool that compares:

- **Sequential vs Concurrent Execution**: Run sorting operations with and without threads
- **Container Performance**: Compare `std::deque` vs `std::vector` implementations
- **Detailed Timing**: Microsecond-precision performance measurements

## Features

- **Dual Execution Modes**: Sequential and concurrent (threaded) execution
- **Performance Analysis**: Detailed timing for each sorting operation
- **Container Comparison**: Side-by-side performance of deque vs vector
- **Verification**: Automatic sorting correctness validation
- **Error Handling**: Comprehensive input validation and error reporting
- **Clean Output**: Formatted console output with success/failure indicators

## Prerequisites

- **C++ Compiler**: GCC, Clang, or MSVC with C++23 support
- **Build Tools**: GNU Make
- **Operating System**: Linux, macOS, or Windows

## Installation & Compilation

### Quick Start
```bash
# Clone the repository
git clone <repository-url>
cd Ford-Johnson-Algorithm-and-Performance

# Compile the project
make

# Run the program
./FJA [options] <numbers...>
```

### Build Targets

```bash
make        # Build release version (C++23)
make test   # Build debug version with additional logging (C++23)
make clean  # Remove object files
make fclean # Remove all build artifacts
make re     # Rebuild from scratch
```

## Usage

### Command Line Options

```
Usage: ./FJA [-t|--threaded] <positive integer> [positive integer ...]

Options:
  -t, --threaded    Run sorting operations concurrently using threads

Arguments:
  positive integer  One or more positive integers to sort (no duplicates allowed)
```

### Examples

#### Sequential Execution (Default)
```bash
# Sort a small set of numbers sequentially
./FJA 3 5 9 7 4 2 1 8 6

# Generate and sort 1000 random numbers
./FJA $(shuf -i 1-100000 -n 1000)
```

#### Concurrent Execution (Threaded)
```bash
# Sort with threading enabled
./FJA -t 3 5 9 7 4 2 1 8 6

# Sort large dataset with threads
./FJA -t $(shuf -i 1-100000 -n 3000)
```

### Sample Output

```
=== Running sequentially (no threads) ===
Total time without threads: 24 us

=== Sorting Verification ===
✓ Deque sorting: SUCCESS
✓ Vector sorting: SUCCESS

=== Individual operation times ===
Time to process a range of 9 elements with std::deque : 15 us
Time to process a range of 9 elements with std::vector: 7 us
Total individual operations time: 22 us
```

## Algorithm Explanation

### Ford-Johnson Algorithm (Merge-Insertion Sort)

The Ford-Johnson algorithm achieves optimal performance through:

1. **Pair Creation**: Input elements are paired and sorted
2. **Recursive Sorting**: Larger elements from pairs are recursively sorted
3. **Main Chain Building**: Constructs an optimal sequence using smaller elements
4. **Binary Insertion**: Uses Jacobsthal numbers to determine insertion order
5. **Efficient Merging**: Combines sorted subsequences optimally

### Key Characteristics

- **Time Complexity**: O(n log n) in practice, theoretically O(n²) worst case
- **Space Complexity**: O(n) additional space
- **Optimal Insertions**: Uses Jacobsthal sequence for minimal comparisons
- **Adaptive Performance**: Excellent for small to medium datasets

## Performance Analysis

### Container Comparison

| Container | Insertion Performance | Access Performance | Memory Layout |
|-----------|----------------------|-------------------|---------------|
| `std::deque` | Excellent (amortized O(1)) | O(1) | Segmented chunks |
| `std::vector` | Good (amortized O(1)) | O(1) | Contiguous |

### Threading Performance

- **Small Datasets (< 100 elements)**: Threading overhead may reduce performance
- **Large Datasets (> 1000 elements)**: Concurrent execution provides significant speedup
- **Container Impact**: Vector generally outperforms deque for this algorithm

### Benchmark Results

Example performance comparison (1000 elements):
- **Sequential**: ~1083 μs total
- **Concurrent**: ~1064 μs total (potential speedup with larger datasets)

## Project Structure

```
Ford-Johnson-Algorithm-and-Performance/
├── main.cpp           # Program entry point and argument handling
├── FJA.cpp           # Ford-Johnson algorithm implementation
├── FJA.hpp           # Algorithm class definitions and templates
├── utils.cpp         # Utility functions (duplicate checking, timing)
├── utils.hpp         # Utility function declarations
├── exceptions.hpp    # Custom exception classes
├── constants.hpp     # Algorithm constants and configurations
├── Makefile          # Build configuration
├── LICENSE           # MIT License
└── README.md         # This file
```

### Key Components

- **`FJA` Class**: Core algorithm implementation with container abstraction
- **Template Methods**: Generic implementation supporting multiple container types
- **Jacobsthal Sequence**: Optimal insertion order generation
- **Binary Search**: Efficient element insertion positioning
- **Threading Support**: Concurrent execution using `std::thread`

## Testing

### Input Validation

The program validates:
- Positive integers only
- No duplicate values
- Reasonable input size limits

### Sorting Verification

Automatic verification ensures:
- Correct sorting order
- All elements preserved
- No data corruption

### Example Test Cases

```bash
# Valid inputs
./FJA 1 2 3 4 5
./FJA -t 10 20 30 40 50

# Invalid inputs (will show errors)
./FJA 1 2 2 3        # Duplicate values
./FJA -1 0 1         # Non-positive numbers
./FJA abc 123        # Non-numeric input
```

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines

- Follow C++20 standards and best practices
- Maintain consistent code formatting
- Add comprehensive error handling
- Include performance tests for new features
- Update documentation for API changes

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **Ford & Johnson**: Original algorithm developers
- **Jacobsthal Numbers**: Mathematical foundation for optimal insertions
- **C++ Standard Library**: Efficient container implementations

## Support

For questions, issues, or contributions:
- Open an issue on GitHub
- Review the source code comments
- Check the algorithm documentation

---

*Made for algorithm enthusiasts and performance optimization*