#include <stdio.h> 
#include <stdlib.h>
#include <time.h>	//used for timing - see last lab.
#include <pthread.h>

#define ARRAY_SIZE 50000000

struct data {
  int* a;
  int start_idx;
  int* sum;
};

void* sum_array(void* arg) {
    struct data thread_data = *(struct data*) arg;

    // @TODO
    // Split the work of summing an input array.
    // HINT: Work should be split half-and-half. Use start_idx
    // to coordinate this.
    // HINT: Make sure to use a lock to synchronize work.
    // +5

    pthread_exit(NULL);
}

int main(void) {
    // @TODO
    // Create and error check a lock
    // +2

    // @TODO
    // Randomly initialize an array.
    // Make sure to error check.
    // +2

    // @TODO
    // Create two pthreads and sum the contents of
    // the randomly initialized array. The time taken
    // and the sum should be recorded and printed.
    // HINT: Use the struct defined above.
    // HINT: Pass your sum variable as a pointer to
    // the threads.
    // +4

    // @TODO
    // Without the use of threads, sum up the randomly initialized array,
    // time the operation, and print out the sum.
    // +2

    // @TODO
    // Check that your serial sum and threaded sum match.
    // If they don't, print an error message and exit (after freeing).
    // +1

    // @TODO
    // Free the memory
    // +1

    return 0;
}
