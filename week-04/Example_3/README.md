# Lab 4 - AoSoA Benchmark

## Example 3 - Results

I completed the AoSoA benchmark using different array sizes (N) and vector lengths (V).

Tested array sizes: 1K, 10K, 100K, 1M and 10M.

Vector lengths: 2, 4, 8, 16, 32, 64, 128 and 256.

## Results

The execution time generally increases as the array size increases.

For larger arrays, increasing the vector length often reduces execution time, although the results are not always consistent.

The results show that memory layout and vector length can affect program performance.

## Google Sheets

The benchmark results and graph are available here:

https://docs.google.com/spreadsheets/d/1MvNv8hU-WjMZmOhHh9M4lyr-MaRI_tf_lAbabYl7kYs/edit?usp=sharing

## Conclusion

AoSoA organizes data into blocks. The benchmark demonstrates how different vector lengths affect execution time and memory access performance.
