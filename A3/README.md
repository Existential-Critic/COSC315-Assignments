# COSC 315: Assignment 3

## Soren Stenback and Baz Sivakua

---

In this assignment, you will work towards creating a producer-consumer application using synchronization concepts discussed in class.

Before getting started, please ensure you have a working starter environment with Docker using the COSC 315 starter code available [here](https://github.com/brikwerk/cosc315-starter). If you have not set this up yet, please follow the instructions available in the starter code repository before working on this assignment.

Additionally, please also ensure you have a working Java development environment (e.g.
Eclipse, IntelliJ, command line, etc). If you do not have a development environment setup,
please reach out to your TA or instructor. This assignment assumes you have used Java for
development before.

| Item | Description |
| --- | --- |
| *Assignment* | Work can be done in **pairs** or individually. If you are submitting as a pair, **only one** team member should submit. For a pair submission, please indicate who your other team member is. |
| *Submission* | Submit your code as a Zip file on Canvas under the appropriate assignment page. Only submit your .c and .java files (ex: P2.c, P1.java, etc).
| *Due Date* | March 18th at 11:59 PM |

## Rubric

| Rubric | Score |
| --- | --- |
| *P1 - Java* | |
| Synchronised Bounded Buffer Operations | /7 |
| Producer Implementation | /5 |
| Consumer Implementation | /5 |
| Main Method | /3 |
| --- | /20 |
| *P2 - C* | |
| Synchronised Bounded Buffer Operations | /7 |
| Producer Implementation | /5 |
| Consumer Implementation | /5 |
| Main Method | /3 |
| --- | /20 |
| *README* | |
| Implementation and Build instructions | /5 |
| --- | /5 |
| Total | /45 |

## Getting Started

This assignment is more free-form than previous assignments. How you design and code the two parts described below is generally up to you. However, please refrain from building something complex that your TA will be unable to compile and reproduce. If there are assumptions made when building or compiling your code, please include a README file explaining any needed instructions.

For Java development, you are free to use your own development environment.

For C development, you are required to continue developing inside the Docker container.

## Implementation

### P1 - Java

For the Java component, the multithreading and bounded buffer were implemented using custom classes and the Runnable package.

The Request class is constructed in such a way to be an object that contains an ID and a time duration. A single constructor is included to set these variables.

The BoundedBuffer class is set to use objects of type T, which is set when creating the buffer. The class includes the buffer variable itself, int variables for the count of items, the producer location, and the consumer locations, as well as two objects to use as locks. For methods, there is a constructor to set the maximum length of the buffer. There is also a produce method to call the producer lock and check if the buffer is full, and then run the producer itself. Once complete, it will call the consumer lock to allow the consumers to run. The consume method will call the consumer lock to see if the buffer is empty, and then run the consumer. Once complete, it will call the producer lock to tell it that there is an open space. There are helper methods written to check if the buffer is full, empty, and to run the producer and consumers.

The Producer class implements the Runnable package, and contains the variables for the BoundedBuffer of type Request, the maximum time a request can have, the minimum time a request can have, and an incrementing request ID. A constructor is included to set the buffer to an existing variable. There is a single method, run(), which calls the start time and then runs repeatedly to create new requests and add them to the buffer and print their information.

The Consumer class also implements the Runnable package, and contains the variables of the Bounded Buffer and the consumer's own ID. The constructor sets both of these to existing variables. The run() method starts a timer and then takes a request out of the buffer and prints its information.

### P2 - C

The C implementation of the Producer-Consumer code uses a multi-threaded program that implements semaphores to synchronize access to the shared buffer. The program initializes a semaphore for the producer and consumers; these indicate the number of empty and full slots in the buffer. The producer thread generates a request with a unique ID and a random length and then adds it to the buffer. Each consumer thread reads a request from the buffer, processes it, and then removes it from the buffer. 

The producer function generates a request and adds it to the buffer using sem_wait and sem_post operations to ensure that the buffer is not full before adding a new request. It then prints a message indicating the request ID, length, and time elapsed before sleeping for one second.

The consumer function reads a request from the buffer using sem_wait and sem_post operations to ensure that the buffer is not empty before reading a request. It then prints a message indicating the request ID, length, and time elapsed before sleeping for the length of the request. Finally, it prints a message indicating that the request has been completed.

## Build

### P1 - Java

To compile and run P1.java, open it in your IDE (VSCode preferably) and execute the file.

### P2 - C

To compile and run P2.c,  open it in your IDE (VSCode preferably), have the docker container outlined in previous assignments open and execute the file.
