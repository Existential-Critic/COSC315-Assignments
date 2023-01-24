# COSC 315: Assignment 1

In this assignment, you will work towards solving problems that require use of standard I/O, memory allocation, and other C functionality.

Before getting started, please ensure you have a working starter environment with Docker using the COSC 315 starter code available [here](https://github.com/brikwerk/cosc315-starter). If you have not set this up yet, please follow the instructions available in the starter code repository before working on this assignment.

| Item | Description |
| --- | --- |
| *Assignment* | Work can be done in **pairs** or individually |
| *Submission* | Submit your code as a Zip file on Canvas under the appropriate assignment page. Only submit your .c and .txt files (ex: Q1.c, Q2.txt, etc).
| *Due Date* | February 4th at 11:59 PM |

## Getting Started

To begin, extract the contents of "A1.zip" to the starter code location on your computer. The folder structure should look something like the following:

![folder_structure](imgs/folder_structure.png)

Next, boot up your Docker container (if not already running) and check that the assignment files are available:

```bash
# Boot container
docker compose up -d # or docker-compose up -d
# Attach a shell to the container
docker exec -it cosc315 /bin/bash # or //bin//bash
# Change directory and view files
cd /cosc315 && ls
# You should see the "A1" directory now
> A1  Dockerfile  README.md  docker-compose.yml  imgs  test.c
# Change directories to the A1 folder and start working on
# the assignment
cd A1
```

Remember that your C programs need to be compiled into an executable with `gcc` and run. `gcc` has been installed and made available to you in the Docker container already. To compile your code, make use of the gcc command line interface (CLI). An example for compiling `Q1.c` is below:

```bash
# The first argument is the path to your source code.
# The second argument, specified with "-o", represents
# the output name of the executable.
gcc Q1.c -o Q1
# Run the file with "./"
./Q1
# You can combine these commands with && so that they
# run with one command
gcc Q1.c -o Q1 && ./Q1
```

Finally, starter files have been provided for you on this assignment. Please read over the contents of these starter files carefully.

## Rubric

The assignment will be marked as follows:

| Rubric | Score |
| --- | --- |
| *Q1* | |
| Specifying and reading a set numbers | /2 |
| Finding min, max, sum and average | /2 |
| Formatting and printing results | /4 |
| --- | /8 |
| *Q2* | |
| Main difference between `calloc` and `malloc` | /2 |
| Speed difference between `calloc` and `malloc` | /2 |
| --- | /4 |
| *Q3* | |
| Read input from user | /2 |
| Allocate with `malloc` and randomly fill an int array | /4 |
| Allocate with `malloc` and create a char array | /4 |
| Format and print output | /2 |
| --- | /12 |
| *Q4* | |
| Read input from user | /2 |
| Opened file descriptor with error checking | /4 |
| Read file contents with error checking | /4 |
| Check file content is an integer | /2 |
| Reverse file content integer | /4 |
| Free memory and close descriptor | /2 |
| --- | /18 |
| Total | /42 |

## Q1

Write C code that reads a user-specified number of integers and calculates the min, max, sum, and average. Additionally, when calculating the average, ensure that decimal values are preserved. E.g. 3/2 should be 1.5, not 1.0.

### Hints

- To read user input, you will need to make use of `scanf`. To find out more info, try running `man scanf` in your Docker container.
- Keep in mind that dividing an integer will result in an integer, even if the result is being assigned to a float. Try casting an integer to a float before division to prevent decimal truncation.

### Example Output

```bash
Enter how many numbers you wish to use: 5
# Negative numbers can be supplied by the user
Enter 5 numbers separated by spaces: -1 2 5 4 8
Min: -1, Max: 8, Sum: 18, Avg: 3.60
```

```bash
Enter how many numbers you wish to use: 4
# Multi-digit integers can be used
Enter 4 numbers separated by spaces: 10 20 30 40
Min: 10, Max: 40, Sum: 100, Avg: 25.00
```

## Q2

Answer the following questions in the `Q2.txt` text file:

### Part A

What is the main difference between `calloc` and `malloc`?

### Part B

Is there any difference in speed between `calloc` and `malloc`?

### Hints

- Try using `man malloc` or `man calloc` to find out more about these C functions.

## Q3

Write C code that creates an array of randomly generated integers with `malloc`. The total size of the array should be of a user-specified length. The randomly generated integers should fall within a certain range of values. Another char array of the same length should be created with `malloc` and filled by casting the integers in the integer array.

### Hints

- An example use of `malloc` for a float array follows:

    ```c
    float* A = (float*) malloc(num_floats * sizeof(float));
    ```

- `malloc` takes one argument: the total number of bytes that are to be claimed out of the system's memory. To correctly allocate memory for an array of a variable type, you need to know how many elements the array should be composed of and how many bytes of memory a variable takes. `sizeof` can be used to determine the byte size of a variable type.
- The returned result from `malloc` needs to be cast to an array type before use. To cast to an array of floats, for example, you would use `(float*)`.
- Random values can be generated with `rand()`. Please note, though, that `srand(time(NULL));` should be run **before** you use `rand()`. If `srand` is not used before `rand`, the same numbers will be generated each program execution.
- Integers can be cast to chars and chars can be cast to integers.
- Arrays created with `malloc` should be freed after finishing with them using `free`.
- `printf("%s", array_of_chars)` can be used to print an entire array of chars.

### Sample Output

```bash
Generating numbers from 40 to 100
Enter how many numbers you wish to generate: 4
Generated numbers: 53 48 59 77 
Random letters: 50;M
```

## Q4

Write C code that reads a user-specified amount of letters from a text file. The read letters are then checked if they form a valid integer (whether or not each letter is a digit, 0-9). A reversed form of the number is printed if the letters are found to form a number.

Additionally, opening and reading the text file must be done with the system calls `open` and `read`. Errors from these system calls should also be handled. For more information on these functions, run `man open` or `man read`.

Finally, the path to the file that is read should be supplied as an *argument* to your C code over the command line. This means that the path should be supplied when running your file. As an example, `Q4.txt`'s path would be supplied as follows:

```bash
# Assuming that the terminal's current working directory
# is at the assignment folder and Q4.c has been compiled
# to Q4
./Q4 Q4.txt
# Running the above makes the argument available to
# the C program.
```

### Hints

- If a function (such as a system call) encounters an error and returns a bad value, the error it encountered can be retrieved and printed with `perror`.
- The `exit` function can be called early to exit the program if an error is encountered. It's good practice to use `exit(1)` in these situations.
- Since you are reading characters from a file, an allocated char array should be used for `read`'s buffer.
- `isdigit` checks if a character is a digit.
- Remember that allocated arrays with `calloc` and `malloc` need to be freed at the end of their usage.
- File descriptors need to be closed with `close` at the end of their usage.

### Sample Output

```bash
How many numbers do you want to read: 4
Getting a file descriptor for Q4.txt
Reading up to 4 numbers from the file
4 bytes read
File contents: 2984
Reversed file content: 4892
```

```bash
How many numbers do you want to read: 10
Getting a file descriptor for Q4.txt
Reading up to 10 numbers from the file
10 bytes read
File contents: 298462384a
File contents are not a number
```

```bash
How many numbers do you want to read: 4
Getting a file descriptor for Q10.txt
Unable to read file: No such file or directory
```
