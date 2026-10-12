# Example 01 - Measuring Time in C and MPI

Before we can talk about whether a parallel program is "faster", we need a reliable way to measure how long something takes. This example shows two ways to do that:

- `Timelt.c` - timing a normal (serial) C program
- `MPITimelt.c` - timing an MPI program that runs on several processes

Both programs do the same thing: start a timer, sleep for 3 seconds (this stands in for "real work"), stop the timer and print the elapsed time. Since we know the work takes 3 seconds, we can check that our timer is giving us the right answer.

## Serial version (`Timelt.c`)

We use `clock_gettime()` with `CLOCK_MONOTONIC`:

```c
clock_gettime(CLOCK_MONOTONIC, &tstart);
sleep(3);
clock_gettime(CLOCK_MONOTONIC, &tstop);
```

`CLOCK_MONOTONIC` is a clock that only moves forward. It is not affected if someone changes the system time while your program is running, which is why it is the right choice for measuring durations.

The result comes back in two parts, seconds (`tv_sec`) and nanoseconds (`tv_nsec`), so we combine them into one number:

```c
elapsed_time = (tstop.tv_sec - tstart.tv_sec) +
               (tstop.tv_nsec - tstart.tv_nsec) / 1.0e9;
```

The `#define _POSIX_C_SOURCE 199309L` at the top is needed because we compile with `-std=c99`, and without it `clock_gettime()` is not visible to the compiler.

## MPI version (`MPITimelt.c`)

MPI gives us its own timer, `MPI_Wtime()`, which returns the current time in seconds as a `double`. No need to combine seconds and nanoseconds yourself.

The important part is the use of `MPI_Barrier()` around the timed section:

```c
MPI_Barrier(MPI_COMM_WORLD);
start_time = MPI_Wtime();

sleep(3);

MPI_Barrier(MPI_COMM_WORLD);
end_time = MPI_Wtime();
```

A barrier makes every process wait until all processes have reached that line. We need this because processes don't start at exactly the same moment. The first barrier makes sure everyone starts the timer together, and the second makes sure we only stop the timer once every process has finished its work. Without the barriers, you would only be measuring one process, not the whole program.

Also notice the `if (rank == 0)` checks. Every process runs the same code, so if all of them printed, you would see the same message 4 times. We let only rank 0 do the printing.

## How to run

Build both programs:

```
make
```

Run the serial version:

```
make run-serial
```

Run the MPI version with 4 processes (the default):

```
make run
```

Change the number of processes:

```
make run NP=2
```

Run the MPI version with 1, 2 and 4 processes one after another:

```
make run-all
```

Clean up the compiled files:

```
make clean
```

If `mpirun` complains that there are "not enough slots", you are asking for more processes than your machine has cores. You can either lower `NP` or run it directly with `mpirun --oversubscribe -n 4 ./mpitime_demo`.

## What you should see

Every run should print something close to 3 seconds, for example `3.000123456`. It will never be exactly 3.000000000, because starting and stopping the timer and waking up from `sleep()` all take a tiny bit of time.

Notice that the MPI time stays around 3 seconds no matter how many processes you use. That's expected: every process sleeps for 3 seconds at the same time, they don't split the work between them. In later weeks we will divide real work across processes, and that's when you will see the time go down.
