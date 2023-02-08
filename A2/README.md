# COSC 315: Assignment 2

In this assignment, you will work towards solving problems that require use of threads, pointers, and other C functionality.

Before getting started, please ensure you have a working starter environment with Docker using the COSC 315 starter code available [here](https://github.com/brikwerk/cosc315-starter). If you have not set this up yet, please follow the instructions available in the starter code repository before working on this assignment.

| Item | Description |
| --- | --- |
| *Assignment* | Work can be done in **pairs** or individually. If you are submitting as a pair, **only one** team member should submit. For a pair submission, please indicate who your other team member is. |
| *Submission* | Submit your code as a Zip file on Canvas under the appropriate assignment page. Only submit your .c and .txt files (ex: Q1.c, Q2.txt, etc).
| *Due Date* | February 18th at 11:59 PM |

## Getting Started

To begin, extract the contents of "A2.zip" to the starter code location on your computer. Similar to Assignment 1, you should start up your Docker container and `cd` to the appropriate A2 directory.

### Compilation Note

When compiling code that requires use of pthreads, you need to add the pthreads flag (`-lpthread`) to your compilation statement. For example with Q2:

```bash
gcc Q2.c -lpthread -o Q2 && ./Q2
```

## Rubric

| Rubric | Score |
| --- | --- |
| *Q1* | |
| Complete `add_array` function | /4 |
| Complete `rand_init` function | /2 |
| Complete Q1.c main | /5 |
| --- | /11 |
| *Q2* | |
| Complete `add_array` function | /5 |
| Complete `rand_init` function | /5 |
| Complete Q2.c main | /12 |
| --- | /22 |
| *Q3* | |
| A) | /2 |
| B) | /3 |
| --- | /5 |
| *Q4* | |
| Complete `sum_array` function | /5 |
| Complete Q4.c main | /12 |
| --- | /17 |
| *Q5* | |
| Remove the need for a lock | /5 |
| --- | /5 |
| Total | /55 |

For a more granular breakdown, please see the provided C source code files for this assignment.

## Q1

Start with the `Q1.c` file in the provided assignment code.

Write a C program that adds two randomly initialized arrays together and saves the result into a third. Ex: `c[i] = a[i] + b[i]`. Additionally, both the `a` and `b` arrays should be initialized with random integers ranging from 0 to 9. The provided function stubs in `Q1.c` should be used. *DO NOT* change the parameters for either function signatures. In the `add_arrays` function, **you should not create any additional local variables**. To accomplish this, you should focus on using pointers and pointer operations.

You should test your code with an array of 50 million integers. If your system is unable to handle this number (or its very slow), you can lower `ARRAY_SIZE` to a lower number. The initialization time, the first ten elements of `c` (the output array), and the total add time should be printed. Make sure to handle situations where memory allocation fails.

### Sample Runs

```bash
Total init time: 905.25 ms
15 11 14 16 12 9 9 9 13 11 
Total add time: 115.57 ms
```

```bash
Not enough memory.
```

## Q2

Start with `Q2.c` in the provided assignment code.

Write a version of Q1 that uses pthreads. Your main goal should be to split the work (AKA parallelization) between different threads for the `rand_init` and `add_arrays` functions. You should only use two threads for this question.

Similar to Q1, you should test with 50 million integers (unless you lowered the value previously). You should also print out the same results as Q1.

### Sample Output

```bash
Total init time: 537.23 ms
2 11 6 11 15 3 12 8 5 13 
Total add time: 202.54 ms
```

```bash
Not enough memory.
```

### Hints

- To use a pthread, you need to define it, create/run it, and wait for it to finish (joining). A simple example is provided below for a single thread:

    ```
    #include <stdio.h> 
    #include <stdlib.h>
    #include <pthread.h>

    void* add(void* arg) {
    	// Cast arg back to int value
        int a = *(int*)arg;
        printf("Value: %d", a);
        pthread_exit(NULL);
    }

    int main(void) {
        int a = 5;
        pthread_t thread1; // Define
        pthread_create(&thread1, 
        	NULL, add, &a); // Create/run
        pthread_join(thread1, 
        	NULL); // Wait for finish
    }
    ```
- Make sure to use `rand_r` rather than `rand` when generating random numbers. To ensure a random seed for each thread, try using `time`, `getpid`, and `pthread_self`.

## Q3

Answer the following in `Q3.txt`:

**A)** In Q2, replace rand_r with rand. Is there a difference in total initialization runtime? If so, why?

**B)** In Q2, is your add operation (thread-based `add_arrays`) faster or slower than the code for Q1? Why or why not?

## Q4

Write a C program that creates a randomly initialized array (50 million integers or less, depending on your system) and sums contents using two threads. The work required to find the sum of the whole array should be evenly split between both threads. Use the `sum_array` function for your threads. You do not need to initialize the array using the threads.

Your code should use a lock to synchronize the add operations between threads (i.e creating an atomic add operation). Make sure to error check all code (locks, arrays, etc). To double check the validity of your threaded solution, you should also implement a non-threaded version of the add operation and check that both the threaded summation and the non-threaded summation match. Finally, the threaded and non-threaded solution should both be timed.

### Sample Output

```bash
Thread Sum: 225007698
Total thread sum time: 4501.60 ms
Serial Sum: 225007698
Total serial sum time: 114.07 ms
```

```bash
Thread Sum: 116047793
Total thread sum time: 144.43 ms
Serial Sum: 225007698
Total serial sum time: 114.07 ms
ERROR: Summations do not match
```

### Hints

- Locks can be created and used as follows:

    ```C
    // Locks are thread safe
    pthread_mutex_t lock; // Create
    // Make sure to error check your lock
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Lock init failed\n");
        return 1;
    }
    pthread_mutex_lock(&lock); // Acquire
    // Critical section
    pthread_mutex_unlock(&lock); // Release
    ```

## Q5

Write a new version of Q4 the removes the need for a lock and critical section. For this question, you can copy your answer from Q4 into `Q5.c` to get started. For this question, continue to use two threads.

### Sample Output

```bash
Thread Sum: 225001126
Total thread sum time: 118.49 ms
Serial Sum: 225001126
Total serial sum time: 114.97 ms
```
