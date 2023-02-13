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
    // Iterate through the arrays using start_idx, with each thread doing half.
    for(int i = thread_data.start_idx;i < ((ARRAY_SIZE/2)+thread_data.start_idx);i++) {
        thread_data.c[i] = thread_data.a[i]+thread_data.b[i];
    }
    // Terminate the thread
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
    // Cast arg to int array
    int *a = (int*)arg;
    // Create a seed for random number generation
    unsigned int s = pthread_self();
    // Use the seed to create ARRAY_SIZE random integers
    for(int i = 0;i < ARRAY_SIZE;i++) {
        a[i] = (rand_r(&s) % (range_end - range_start + 1)) + range_start;
    }
    // Terminate the thread
    pthread_exit(NULL);
}

int main(void) {
    // Initialise clocks and double to calculate time
    clock_t start, end;
    double timeElapsed;
	// @TODO
	// Allocate the source arrays (a, b, c)
    // a and b are the source arrays.
    // c is the result storage array.
    // c[i] should equal a[i] + b[i]
    // Make sure to error check.
    // +1
    int *a = (int*) malloc(ARRAY_SIZE * sizeof(int));
    int *b = (int*) malloc(ARRAY_SIZE * sizeof(int));
    int *c = (int*) malloc(ARRAY_SIZE * sizeof(int));
    // Check if any of the arrays are null
    if((a == NULL) || (b == NULL) || (c == NULL)) {
        printf("Not enough memory.");
        return 0;
    }

    // @TODO
    // Create two pthreads and initialize a and b with
    // random numbers using both threads. The full operation
    // should be timed and the period printed.
    // +4
    // Start the clock
    start = clock();
    // Initialise the pthreads
    pthread_t thread1,thread2;
    // Run the pthreads
    pthread_create(&thread1,NULL,rand_init,a);
    pthread_create(&thread2,NULL,rand_init,b);
    // Join the pthreads and wait for them to finish
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    // End the clock
    end = clock();
    // Calculate time passed in milliseconds
    timeElapsed = ((double) (end-start))/(CLOCKS_PER_SEC/1000);
    // Print out the duration message
    printf("Total init time: %.2f ms\n",timeElapsed);

    // @TODO
    // Define and prepare two structs for each thread.
    // The structs should contain data relevent to the add operation.
    // +2
    // Initialise the structs
    struct data data1;
    struct data data2;
    // Initialise the struct pointers
    struct data *d1P = &data1;
    struct data *d2P = &data2;
    // Enter data for the first struct
    data1.a = a;
    data1.b = b;
    data1.c = c;
    data1.start_idx = 0;
    // Enter data for the second struct
    data2.a = a;
    data2.b = b;
    data2.c = c;
    data2.start_idx = (ARRAY_SIZE/2);

    // @TODO
    // Reuse your pthreads from earlier and time your add_arrays function
    // as it runs on both threads.
    // +2
    // Start the clock
    start = clock();
    // Run the pthreads
    pthread_create(&thread1,NULL,add_arrays,d1P);
    pthread_create(&thread2,NULL,add_arrays,d2P);
    // Join the pthreads and wait for them to finish
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    // End the clock
    end = clock();

    // @TODO
    // Print out the first 10 elements of the result array and the final
    // period for the add_arrays threaded function runs.
    // +2
    // Iterate through array c and prin t the first 10 elements of the array
    for(int i = 0;i < 10;i++) {
        printf("%d ",c[i]);
    }
    // Print a new line
    printf("\n");
    // Calculate time passed in milliseconds
    timeElapsed = ((double) (end-start))/(CLOCKS_PER_SEC/1000);
    // Print out the duration message
    printf("Total add time: %.2f ms\n",timeElapsed);

    // Free the memory
    // +1

    return 0;
    free(a);
    free(b);
    free(c);
}
