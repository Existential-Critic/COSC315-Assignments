#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // argv[1] gets us the path passed as an argument to
    // our executed program.
    char *filename = argv[1];
    int nums_to_read;

    // 1. Get how many numbers we want to read
    printf("How many numbers do you want to read: ");

    // 2. Attempt to get the file descriptor for our file
    // HINT: Make sure to properly error check the output
    // from the system call.
    printf("Getting a file descriptor for %s\n", filename);

    // 3. Attempt to read the file's contents
    // HINT: A calloc-made char array can be used as a buffer
    //      An example for a float array follows:
    //      float *a = (float *) calloc(num_of_floats, sizeof(float));
    // HINT: Make sure to properly error check the output from the
    // system call.
    printf("Reading up to %d numbers from the file\n", nums_to_read);

    // 4. Check that the read content is an integer
    
    // 5. Reverse and print the file content, if it is a number

    // 6. Free memory from calloc and close open file descriptors

    return 0;
}