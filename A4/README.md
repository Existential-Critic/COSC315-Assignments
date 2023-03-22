# COSC 315: Assignment 4

In this assignment, you will work towards solving problems that require use of bit-wise operations, file reading, memory allocation theory, and other C functionality.

Before starting, please ensure you have a working starter environment with Docker using the COSC 315 starter code available [here](https://github.com/brikwerk/cosc315-starter). If you have not set this up yet, please follow the instructions available in the starter code repository before working on this assignment.

| Item | Description |
| --- | --- |
| *Assignment* | Work can be done in **pairs** or individually. If you are submitting as a pair, **only one** team member should submit. For a pair submission, please indicate who your other team member is. |
| *Submission* | Submit your code as a Zip file on Canvas under the appropriate assignment page. Only submit your .c files (ex: Q1.c).
| *Due Date* | April 1st at 11:59 PM |

<div style="page-break-after: always;"></div>

## Rubric

| Rubric | Score |
| --- | --- |
| *Q1* | |
| Check for command line interface filename argument | /1 |
| Open file for reading | /2 |
| Check if the opened file is valid | /1 |
| Retrieve the n lower bits from the file | /2 |
| Retrieve the m upper bits from the file | /2 |
| Loop through addresses | /1 |
| For each address, retrieve the offset | /6 |
| For each address, retrieve the page number | /6 |
| For each address, print out the page number and offset | /1 |
| Close your open file | /2 |
| --- | /24 |

## Getting Started

This purpose of this assignment is to implement a portion of the virtual to physical address translation in a pure paging based scheme (e.g. no TLB, segmentation, etc). Your goal is to write a program that takes a sequence of virtual addresses (as integers recorded in a text file) and extract the page number and offset for each address using bit-wise operations.

Assume that virtual addresses are unsigned integers (i.e., unsigned int) and that we only look at 16 bits of the integer representing a virtual address. Thus, even if your machine represents integers as 32 or 64 bits, we are only concerned with the lower 16 bits of an integer to represent the virtual address. Your program should take the following inputs from an input file (comments not included):

```c
// The n lowest significant bits
// that represent the offset.
n
// The m upper bits that represent
// the page number. Assume that
// n+m will always be 16.
m
// The first virtual address that
// needs to be mapped to a page number
// and an offset.
v1
// The second virtual address
v2
// An input file can contain a sequence
// of virtual address, one per line,
// until the end of the file.
...
```

For an example file, take a look at the provided `example_input_1.txt`.

Your program should read the above a given file, and in particular, read each virtual address as an unsigned integer and compute and print out the page number and offset for each address. Assume that the virtual addresses are correct and no error checks are needed. To compute the offset, use bit operations in C to extract the n least significant bits from an address (v) and print out the resulting integer. To compute the page number, extract the next m significant bits from v and print out the integer representing these bits.

You can check the result of your program by hand-computing the page number and offset as v DIV 2^n and v MOD 2^n However your program should not use division and mod operations to compute these values and should use bit-wise operations instead (just as a hardware implementation of paging would use).

The output of your program should look like the following when run against `example_input_1.txt:

```bash
Reading file: example_input_1.txt
virtual address v1 is in page number 98 and offset 163
virtual address v2 is in page number 19 and offset 70
virtual address v3 is in page number 202 and offset 253
```

<div style="page-break-after: always;"></div>

## Hints

- Bit-wise operations in C involve binary manipulation. A summary of bit-wise operations can be found [here](http://www.cprogramming.com/tutorial/bitwise_operators.html). Pay particular attention to the right shift operator as well as the using bit-masks and the bit-wise AND operation, which are concepts that will be helpful for this assignment.
- You should use unsigned integers when working with the addresses (just like regular memory allocation techniques would). To do this in C, use the `unsigned` prefix when defining an integer. E.g. `unsigned int x = 0;`
- When reading a file, you can use fopen and fclose. For more info on these functions, you can refer to the man pages (e.g. `man fopen`).
- Reading a line from a file can be done using fgets.
- To check your work and explore bit-wise operations, you can examine the binary value of a given address (you can convert decimals online [here](https://www.rapidtables.com/convert/number/decimal-to-binary.html)). The upper bits and lower bits of binary can be converted back to decimals values to get your page number and offset.
- Try changing the n and m values to make sure your code still works. n+m should still add up to 16, though.

## Submitting Your Assignment

1. Your zip file should contain a copy of all source files and the name of both partners in a text file (if you partnered up).

2. Submit your zip file on Canvas under the appropriate assignment.
