#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int range_start = 40, range_end = 100;
    printf("Generating numbers from %d to %d\n",range_start,range_end);

    // Initialise the variable which will contain how many numbers we are working with.
    int numNums;
    // Print the message asking for the amount of numbers.
    printf("Enter how many numbers you wish to generate: ");
    // Take in the next entered integer and save it to numNums.
    scanf("%d",&numNums);

    // Initialise the array using malloc and the provided size above.
    int *arrRandom = (int*) malloc(numNums * sizeof(int));
    // Use srand to seed for random generator.
    srand(time(NULL));
    // Iterate through the array and fill each space with a random number in the range.
    for(int i = 0;i < numNums;i++) {
        arrRandom[i] = rand() % (range_end-range_start+1) + range_start;
    }

    // Begin the printed message.
    printf("Generated numbers:");
    // Iterate through the array and print each number with a space before it.
    for(int i = 0;i < numNums;i++) {
        printf(" %d",arrRandom[i]);
    }
    // Finish by printing a new line.
    printf("\n");

    // Initialise the array using malloc and the provided size above.
    char *arrCharCast = (char*) malloc(numNums * sizeof(char));
    // Iterate through the array and fill each space with the equivalent random int casted to char.
    for(int i = 0;i < numNums;i++) {
        arrCharCast[i] = (char)arrRandom[i];
    }

    // Begin the printed message.
    printf("Random letters: ");
    // Print the full array as a string.
    printf("%s",arrCharCast);
    // Finish by printing a new line.
    printf("\n");

    return 0;
}