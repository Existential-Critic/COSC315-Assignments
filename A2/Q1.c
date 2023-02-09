#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 50000000

void add_arrays(int* result, int* a, int* b, int array_size) {
    // @TODO
	// Add a + b together and store in the result array.
    // DO NOT create any local variables in this function.
    // +4
    // Iterate through the array using a pointer; if this counts as a local variable I got nothing chief
    for(int *p = a; a < (p+array_size);) {
        // Set the place the pointer points to equal the sum of the other two pointer places
        *result = (*a + *b);
        // Increment each pointer
        result++;
        a++;
        b++;
    }
}

void rand_init(int* a, int array_size) {
    // @TODO
    // Randomly initialize an array of size array_size
    // using numbers between 0 and 9.
    // +2
    int range_start = 0;
    int range_end = 9;
    // Iterate through the memory allocated and fill with random numbers
    for(int *p = a;a < (p+array_size);) {
        // Generate a random integer between the start and end of the range
        *a = (rand() % (range_end - range_start + 1)) + range_start;
        // Increment the pointer
        a++;
    }
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
    // Initialize the two arrays, a and b, with random values 
    // of size ARRAY_SIZE and measure the time it takes to do so.
    // +1
    // Start the clock
    start = clock();
    // Call rand_init() on both a and b
    srand(time(NULL));
    rand_init(a,ARRAY_SIZE);
    rand_init(b,ARRAY_SIZE);
    // End the clock
    end = clock();

    // @TODO
    // Print the total time for initialization
    // +1
    // Calculate time passed in milliseconds
    timeElapsed = ((double) (end-start))/(CLOCKS_PER_SEC/1000);
    // Print out the duration message
    printf("Total init time: %.2f ms\n",timeElapsed);

    // @TODO
    // Run and time the add operation, print the first ten elements
    // of the result array, and print the total add time.
    // +2
    // Start the clock
    start = clock();
    // Call add_arrays() with a, b, and c
    add_arrays(c,a,b,ARRAY_SIZE);
    // Iterate through and print the first 10 elements of the array
    for(int i = 0;i < 10;i++) {
        printf("%d ",c[i]);
    }
    // Print a new line
    printf("\n");
    // End the clock
    end = clock();
    // Calculate time passed in milliseconds
    timeElapsed = ((double) (end-start))/(CLOCKS_PER_SEC/1000);
    // Print out the duration message
    printf("Total add time: %.2f ms\n",timeElapsed);

    return 0;
}
