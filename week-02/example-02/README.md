# Example 02 - Finding Memory Bugs with Valgrind

Memory bugs in C are tricky because the program often runs fine and prints the right output, even though something is wrong underneath. In parallel programs these bugs get even harder to track down, so it's worth learning how to catch them early.

This example has two files:

- `memory_leak.c` - a small program with three common memory mistakes
- `memory_leak_fix.c` - the same program written correctly

We use a tool called Valgrind to find the problems in the first file.

## The bugs in `memory_leak.c`

The program allocates space for 5 integers and then makes three mistakes.

**Bug 1: Reading memory before giving it a value**

```c
printf("First element: %d\n", arr[0]);
```

`malloc()` does not set the memory to zero. Whatever was there before is still there, so `arr[0]` could be any number.

**Bug 2: Writing past the end of the array**

```c
for (int i = 0; i <= n; i++) {
```

The array has 5 elements (indexes 0 to 4), but `i <= n` also runs for `i = 5`. That writes into memory that doesn't belong to us. Sometimes this crashes, sometimes it silently overwrites other data, which is even worse.

**Bug 3: Memory leak**

```c
// free(arr);
```

The memory is never freed. In a tiny program like this it doesn't hurt much, but in a long running program that allocates memory in a loop, it will slowly eat up all the RAM.

The program also doesn't check if `malloc()` returned `NULL`, which happens when the allocation fails.

## The fixed version (`memory_leak_fix.c`)

The fixed version solves each problem:

- checks that `malloc()` didn't return `NULL`
- sets every element to 0 before using it
- uses `i < n` so the loop stays inside the array
- calls `free(arr)` at the end, and sets `arr = NULL` so we can't accidentally use it again

## How to run

Build and run the buggy program normally:

```
make run
```

You will probably see it run without any errors. That's the point: the bugs are there, you just can't see them.

Now run it under Valgrind:

```
make valgrind
```

There is also a shorter version with less output:

```
make valgrind-simple
```

To run the fixed program, normally and under Valgrind:

```
make run-fix
make valgrind-fix
```

Clean up:

```
make clean
```

Note: Valgrind works on Linux. It is not available on newer Macs (Apple Silicon), so use the lab machines or a Linux VM for this example.

## Reading the Valgrind output

For the buggy program, look for these lines:

- `Conditional jump or move depends on uninitialised value(s)` - this is Bug 1, using `arr[0]` before it had a value
- `Invalid write of size 4` - this is Bug 2, writing one `int` (4 bytes) past the end of the array
- `definitely lost: 20 bytes in 1 blocks` - this is Bug 3, the 5 integers (5 x 4 = 20 bytes) we never freed

Valgrind also shows the line number where each problem happened. That works because the Makefile compiles with `-g`, which keeps debug information in the program.

For the fixed program you should see:

```
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

That's what you want to see for your own programs too. Get in the habit of running your assignments through Valgrind before you submit them.
