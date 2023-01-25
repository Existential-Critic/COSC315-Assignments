#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initialise the variable which will contain how many numbers we are working with.
    int numNums;
    // Print the message asking for the amount of numbers.
    printf("Enter how many numbers you wish to use: ");
    // Take in the next entered integer and save it to numNums.
    scanf("%d",&numNums);

    // Initialise the array of the size provided previously.
    int arrNum[numNums];
    // Print the message asking for a number of integers as provided above.
    printf("Enter %d numbers separated by spaces: ", numNums);
    // Create a for loop that will iterate through the array and insert numbers as entered.
    for(int i = 0;i < numNums;i++) {
        scanf("%d",&arrNum[i]);
    }

    // Initialise variables to contain the numbers we need.
    int minLoc = 0, maxLoc = 0;
    float sum = 0.0, avg;
    // Iterate through the array and calculate the minimum/maximum locations and the sum of the array.
    for(int i = 0;i < numNums;i++) {
        if(arrNum[i] > arrNum[maxLoc]) {
            maxLoc = i;
        }
        if(arrNum[i] < arrNum[minLoc]) {
            minLoc = i;
        }
        sum += arrNum[i];
    }
    // With the sum, calculate the average of the array.
    avg = sum/numNums;

    // Print the calculated statistics of the array.
    printf("Min: %d, Max: %d, Sum: %.0f, Avg: %.2f\n",arrNum[minLoc],arrNum[maxLoc],sum,avg);

    return 0;
}