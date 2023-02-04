#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // argv[1] gets us the path passed as an argument to
    // our executed program.
    char *filename = argv[1]; 
    int nums_to_read; //number of letters to read

    // 1. Get how many numbers we want to read
    printf("How many numbers do you want to read: ");
    scanf("%d", &nums_to_read); //read in number from user

    // 2. Attempt to get the file descriptor for our file
    // HINT: Make sure to properly error check the output
    // from the system call.
    printf("Getting a file descriptor for %s\n", filename);
    int fd = open(filename, O_RDONLY); //open file in read only
    if (fd == -1) {//if file cannot be opened, print message
        printf("Error opening the file \n");
        close(fd); //close file descriptor fd
        return 1;
    }
    //printf("File descriptor for the file: %d\n", fd);

    // 3. Attempt to read the file's contents
    // HINT: A calloc-made char array can be used as a buffer
    //      An example for a float array follows:
    //      float *a = (float *) calloc(num_of_floats, sizeof(float));
    // HINT: Make sure to properly error check the output from the
    // system call.
    printf("Reading up to %d numbers from the file\n", nums_to_read);
    char *buffer = (char *) calloc(nums_to_read, sizeof(char));// array of characters to store chars from file
    int read_char = read(fd, buffer, nums_to_read);//
    buffer[read_char] = '\0'; //make sure stored items are null terminated
    printf("File contents: %s\n", buffer);//print chars read from file

    // 4. Check that the read content is an integer
    for (int i = 0; i < nums_to_read; i++){//for loop checking digit
        if (isdigit(buffer[i]) == 0){//if the chars read are not numbers print message
            printf("File contents are not a number \n");
            free(buffer); //free buffer
            close(fd); //close file descriptor fd
            return 0;//end program
        }
    }
    
    // 5. Reverse and print the file content, if it is a number
    int temp; //temp variable to store items from array to move it
    for (int i = 0, j = nums_to_read - 1; i < j; i++, j--){//for loop reversing number
        temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }
    printf("Reversed file content: %s\n", buffer);

    // 6. Free memory from calloc and close open file descriptors
    free(buffer); //free buffer
    close(fd); //close file descriptor fd

    return 0;
}
