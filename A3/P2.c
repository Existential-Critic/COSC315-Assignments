#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 

//Declare global variables
sem_t producerSem, consumerSem;
int producerPos = 0, consumerPos = 0, count = 0;
void* producer(void* arg);
void* consumer(void* arg);

struct Request {
    int reqID;
    int length;
};
struct Request buffer[BUFFER_SIZE];

int main() {
    // Initialize semaphores
    sem_init(&producerSem, 0, BUFFER_SIZE);
    sem_init(&consumerSem, 0, 0);

    // Create Producer thread
    pthread_t producerThread;
    pthread_create(&producerThread, NULL, producer, NULL);

    // Create scanner to read user input
    int numConsumers;
    printf("How many consumer threads are there?\n");
    scanf("%d", &numConsumers);

    // Create Consumer threads
    pthread_t consumerThreads[numConsumers];
    for (int i = 0; i < numConsumers; i++) {
        pthread_create(&consumerThreads[i], NULL, consumer, (void*) (long) (i + 1));
    }

    // Join all threads
    pthread_join(producerThread, NULL);
    for (int i = 0; i < numConsumers; i++) {
        pthread_join(consumerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&producerSem);
    sem_destroy(&consumerSem);

    return 0;
}

void* producer(void* arg) {
    // Initialize needed variables
    int maxTime = 10, minTime = 1, reqId = 0;
    struct Request newReq;
    while (1) {
        reqId++;
        newReq.reqID = reqId;
        newReq.length = rand() % (maxTime - minTime + 1) + minTime;

        sem_wait(&producerSem);
        buffer[producerPos] = newReq;
        if (++producerPos == BUFFER_SIZE) {
            producerPos = 0;
        }
        count++;
        sem_post(&consumerSem);

        float timeElapsed = (float) (clock()) / CLOCKS_PER_SEC;
        printf("Producer: Produced request ID %d, length %d seconds at time %f.\n", newReq.reqID, newReq.length, timeElapsed);
        printf("Sleeping for 1 second.\n");
        sleep(1);
    }
}

void* consumer(void* arg) {
    // Initialize needed variables
    int consumerId = (int) (long) arg;
    struct Request consumerReq;
    while (1) {
        sem_wait(&consumerSem);
        consumerReq = buffer[consumerPos];
        if (++consumerPos == BUFFER_SIZE) {
            consumerPos = 0;
        }
        count--;
        sem_post(&producerSem);

        float timeElapsed = (float) (clock()) / CLOCKS_PER_SEC;
        printf("Consumer %d: Assigned request ID %d, processing request for the next %d seconds, current time is %f.\n", consumerId, consumerReq.reqID, consumerReq.length, timeElapsed);
        sleep(consumerReq.length);
        timeElapsed = (float) (clock()) / CLOCKS_PER_SEC;
        printf("... completed request ID %d at time %f.\n", consumerReq.reqID, timeElapsed);
    }
}
