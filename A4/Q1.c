#include <stdio.h>
#include <stdlib.h>
#define MAXFILENAME 100

// THIS IS ALL DONE ASSUMING THAT ANY FILE SUBMITTED HAS M AND N AS THE FIRST 2 INTS AND EACH INT IS ON A NEW LINE

int main(int argc, char *argv[]) {
    // INITIALISATION
    // Initialise ints n and m to store the offset and page number
    int n,m;
    // Initialise variables to get number of lines from file
    FILE *filePointer;
    int lineCount = 1;
    char fileName[MAXFILENAME];
    char c;
    // Get file name from user
    printf("Enter file name: ");
    scanf("%s",fileName);
    // Open the file
    filePointer = fopen(fileName,"r");
    // Check if file exists
    if(!filePointer) {
        // Handle error
        printf("Error, file does not exist.\n");
        exit(1);
    }
    // Increment lineCount for every '\n' character
    for(c = getc(filePointer);c != EOF;c = getc(filePointer)) {
        if(c == '\n') {
            lineCount++;
        }
    }
    fclose(filePointer);
    // Initialise arrays to contain the virtual addresses, the offsets, and the page numbers
    unsigned int *virAdd = (int*)malloc((lineCount-2)*sizeof(int));
    unsigned int *virAddPageNum = (int*)malloc((lineCount-2)*sizeof(int));
    unsigned int *virAddOffset = (int*)malloc((lineCount-2)*sizeof(int));

    // READ FILE TO SAVE DATA
    // Open file
    filePointer = fopen(fileName,"r");
    // Initalise int variable to read from file
    int fileInt = 0;
    // Iterate through file and read each int, saving into proper value
    for(int i = 0;i < lineCount;i++) {
        fscanf(filePointer,"%d",&fileInt);
        if(i == 0) {
            m = fileInt;
        }else if(i == 1) {
            n = fileInt;
        }else {
            virAdd[i-2] = fileInt;
        }
    }
    // Close file
    fclose(filePointer);

    // CALCULATE OFFSETS AND PAGE NUMBERS
    // Iterate through ints and use bit shifting to get page number and offset
    for(int i = 0;i < (lineCount-2);i++) {
        virAddPageNum[i] = (virAdd[i]>>m);
        virAddOffset[i] = (virAdd[i]&((1<<n)-1));
    }

    // PRINT OUTPUT
    // Print the file name
    printf("Reading file: %s\n",fileName);
    for(int i = 0;i < lineCount-2;i++) {
        printf("Virtual Address v%d is in page number %d and offset %d\n",(i+1),virAddPageNum[i],virAddOffset[i]);
    }

    // FREE MEMORY
    free(virAdd);
    free(virAddPageNum);
    free(virAddOffset);

    // End of code
    return 0;
}