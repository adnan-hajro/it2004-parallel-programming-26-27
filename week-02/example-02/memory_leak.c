#include <stdio.h>
#include <stdlib.h>

int main() {
  int *arr;
  int n = 5;

  // Allocate memory, but forget to check if malloc succeeded
  arr = (int *)malloc(5 * sizeof(int));

  // Bug 1: Use uninitialized memory
  printf("First element: %d\n", arr[0]);

  // Bug 2: Write past allocated memory (out-of-bounds)
  for (int i = 0; i <= n; i++) {
    arr[i] = i * 10;
  }

  // Bug 3: Memory Leak (forgot to free)
  // free(arr);

  return 0;
}