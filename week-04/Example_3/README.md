# Lab 4 - AoSoA Benchmark

## Example 3

In this lab I worked on the AoSoA example and tested how vector size affects execution time.

## What I did

First I opened the project in terminal and went to Example_3 folder.

I opened `aosoa_measurement.cpp` using nano and added the missing code for AoSoA.

After that I saved the file and compiled it using g++ to check if there are errors.

At first I had some errors in the code so I fixed them and compiled again.

Then I ran the benchmark script to test different values.

I tested:

- N = 1K, 10K, 100K, 1M, 10M
- V = 2, 4, 8, 16, 32, 64, 128, 256

The program saved the results in CSV files.

## Results

I opened the CSV files and copied the results into Google Sheets.

I made a graph to compare execution times for different N and V values.

I noticed that bigger arrays take more time to execute.

Changing V sometimes made the program faster but not always.

Google Sheets:
https://docs.google.com/spreadsheets/d/1MvNv8hU-WjMZmOhHh9M4lyr-MaRI_tf_lAbabYl7kYs/edit?usp=sharing

## Conclusion

I learned how AoSoA works with blocks of data and how changing vector size can affect execution time.
