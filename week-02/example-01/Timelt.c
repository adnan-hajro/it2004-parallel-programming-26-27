#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  struct timespec tstart, tstop;
  double elapsed_time;

  printf("=== Serial Timing Test ===\n");

  clock_gettime(CLOCK_MONOTONIC, &tstart);

  printf("Working for 3 seconds... \n");
  sleep(3);

  clock_gettime(CLOCK_MONOTONIC, &tstop);

  elapsed_time = (tstop.tv_sec - tstart.tv_sec) +
                   (tstop.tv_nsec - tstart.tv_nsec) / 1.0e9;

  printf("Elapsed time: %.9f seconds\n", elapsed_time);
  printf("Expected: ~3.000000000 seconds\n");

  return 0;
}