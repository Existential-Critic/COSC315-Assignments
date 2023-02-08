#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define ARRAY_SIZE 50000000

// The following is a struct in C.
// This paradigm allows for arbitrary data to be stored
// in a structured way. This also allows for multiple
// parameters to be passed to a thread function.
// You should use this struct with the add_arrays
// function when running using threads.
struct data {
  int* a;
  int* b;
  int* c;
  int start_idx; // Where the thread should start in an array
};

void* add_arrays(void* arg) {
	struct data thread_data = *(struct data*) arg;
    // Elements from the thread_data struct can be accessed here
    // Ex thread_data.a

    // @TODO
    // Split the work of c[i] = a[i] + b[i] between two threads.
    // HINT: Work should be split half-and-half. Use start_idx
    // to coordinate this.
    // +5

    pthread_exit(NULL);
}

void* rand_init(void* arg) {
    int range_start = 0;
    int range_end = 9;

    // @TODO
    // Fill an array with random variables using a thread.
    // Remember to use rand_r and not rand. You will also need to
    // change how the random seed is calculated such that it is unique
    // for each thread. For more details, see the assignment PDF or README.
    // HINT: The input parameter should be an array, not a struct.
    // +5

    pthread_exit(NULL);
}

int main(void) {
	// @TODO
	// Allocate the source arrays (a, b, c)
    // a and b are the source arrays.
    // c is the result storage array.
    // c[i] should equal a[i] + b[i]
    // Make sure to error check.
    // +1

    // @TODO
    // Create two pthreads and initialize a and b with
    // random numbers using both threads. The full operation
    // should be timed and the period printed.
    // +4

    // @TODO
    // Define and prepare two structs for each thread.
    // The structs should contain data relevent to the add operation.
    // +2

    // @TODO
    // Reuse your pthreads from earlier and time your add_arrays function
    // as it runs on both threads.
    // +2

    // @TODO
    // Print out the first 10 elements of the result array and the final
    // period for the add_arrays threaded function runs.
    // +2

    // Free the memory
    // +1

    return 0;
}
