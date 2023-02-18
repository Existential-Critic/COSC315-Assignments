#include <stdio.h> 
#include <stdlib.h>
#include <time.h>	//used for timing - see last lab.
#include <pthread.h>

#define ARRAY_SIZE 50000000

struct data {
  int* a;
  int start_idx;
  int* sum;
  pthread_mutex_t* lock;
};

void* sum_array(void* arg) {
    struct data thread_data = *(struct data*) arg;
    // @TODO
    // Split the work of summing an input array.
    // HINT: Work should be split half-and-half. Use start_idx
    // to coordinate this.
    // HINT: Make sure to use a lock to synchronize work.
    // +5
    int i, sum = 0;
    for (i = thread_data.start_idx; i < thread_data.start_idx + (ARRAY_SIZE / 2); i++) {
    sum += thread_data.a[i];
    }
    
    // acquire the lock and add the partial sum to the shared variable
    pthread_mutex_lock(thread_data.lock);
    *(thread_data.sum) += sum;
    pthread_mutex_unlock(thread_data.lock);

    pthread_exit(NULL);
}

int main(void) {
    // @TODO
    // Create and error check a lock
    // +2
    pthread_mutex_t lock;
    int err;
    if ((err = pthread_mutex_init(&lock, NULL)) != 0) {
        printf("Error: Failed to initialize lock. Error code: %d\n", err);
        return 1;
    }

    // @TODO
    // Randomly initialize an array.
    // Make sure to error check.
    // +2
    int *a = (int*) malloc(ARRAY_SIZE * sizeof(int)); // Cast arg to int array
    if((a == NULL)) {// Check if any of the arrays are null
        printf("Not enough memory.");
        return 0;
    }
    int i;
    unsigned int seed = time(NULL);// initialize random number generator 
    for (i = 0; i < ARRAY_SIZE; i++) { // fill array with random integers
        a[i] = rand_r(&seed);
    }

    // @TODO
    // Create two pthreads and sum the contents of
    // the randomly initialized array. The time taken
    // and the sum should be recorded and printed.
    // HINT: Use the struct defined above.
    // HINT: Pass your sum variable as a pointer to
    // the threads.
    // +4
    double timeElapsed;
    clock_t start, end;
    int sum = 0;
    start = clock(); //start clock
    pthread_t thread1,thread2; // Initialise the pthreads
    
    struct data thread_data1 = { a, 0, &sum, &lock };
    struct data thread_data2 = { a, ARRAY_SIZE / 2, &sum, &lock };

    pthread_create(&thread1, NULL, sum_array, &thread_data1);
    pthread_create(&thread2, NULL, sum_array, &thread_data2);
    pthread_join(thread1,NULL);// Join the pthreads and wait for them to finish
    pthread_join(thread2,NULL);
    end = clock();// End the clock
    timeElapsed = ((double) (end-start))/(CLOCKS_PER_SEC/1000);// Calculate time passed in milliseconds
    
    printf("Thread Sum: %d\n", sum);
    printf("Total thread sum time: %.2f ms\n",timeElapsed); // Print out the duration message  
    //pthread_exit(NULL);

    // @TODO
    // Without the use of threads, sum up the randomly initialized array,
    // time the operation, and print out the sum.
    // +2
    int serial_sum = 0;
    start = clock();
     for (int i = 0; i < ARRAY_SIZE; i++) {
        serial_sum += a[i];
    }
    end = clock();// End the clock
    timeElapsed = ((double) (end-start))/(CLOCKS_PER_SEC/1000);// Calculate time passed in milliseconds
    printf("Serial Sum: %d\n", serial_sum);

    // @TODO
    // Check that your serial sum and threaded sum match.
    // If they don't, print an error message and exit (after freeing).
    // +1
    if (serial_sum == sum){
        printf("Total serial sum time: %.2f ms\n",timeElapsed);
    } else {
        printf("ERROR: Summations do not match.\n");
    }
    // @TODO
    // Free the memory
    // +1
    free(a);
    pthread_mutex_destroy(&lock);

    return 0;
}
