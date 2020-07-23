#include <stdio.h>
#include <stdlib.h>

#define INPUTSIZE 80
#define BASENUMTESTS 100

int transformBinary(int* numbers, int* binaryVec) {
    int i, j;
    int counter = 0;

    // For every 8 bits
    for(i=0; i < 4; i++) {
        for(j=0; j<8; j++) {
            binaryVec[counter++] = (numbers[i] & 0x80) ? 1 : 0;
            numbers[i] <<= 1;
        }
    }
}

int main() {
    // General Variables
    int i, j, k;

    // Reading Variables
    char readingBuffer[80];
    int numAvailable;
    int numTest = 0;
    char **availableAddresses;
    char **testAddresses;

    // Verification Variables
    int octAvailable[4];
    int octTest[4];
    int binAvailableAddress[32];
    int binTestAddress[32];
    int nBits, success, bestIndex, bestRange;
    int val1, val2, val3, val4;

    // Formatting
    int valBits;
    char local[80];

    // Read Amount of Available Addresses
    fgets(readingBuffer, 20, stdin);
    sscanf(readingBuffer, "%d", &numAvailable);

    // Read Available Addresses and Allocate Memory
    availableAddresses = (char **) malloc(numAvailable * sizeof(char*));

    for(i=0; i<numAvailable; i++) {
        availableAddresses[i] = (char *) malloc(INPUTSIZE * sizeof(char));
        fgets(availableAddresses[i], INPUTSIZE, stdin);
    }

    // Read Test Addresses and Allocate Memory
    testAddresses = (char **) malloc(BASENUMTESTS * sizeof(char*));
    while(1) {

        // Dynamic Memory Allocation as Necessary
        if(numTest > sizeof(testAddresses)/(INPUTSIZE * sizeof(char))) {
            testAddresses = (char **) realloc(testAddresses, numTest * 2 * sizeof(char*));
        }

        // Read Test Addresses
        testAddresses[numTest] = (char *) malloc(INPUTSIZE * sizeof(char));
        fgets(testAddresses[numTest], INPUTSIZE, stdin);
        numTest++;

        // Stop at the End of the File
        if(feof(stdin)) {
            break;
        }
    }

    // Analyse Test Addresses
    for(i=0; i<numTest - 1; i++) {

        // Obtain Binary Representation of Test Addresses
        sscanf(testAddresses[i], "%d.%d.%d.%d", &octTest[0], &octTest[1], &octTest[2], &octTest[3]);
        transformBinary(octTest, binTestAddress);

        // Restart Verification Variables
        bestIndex = -1;
        bestRange = 0;
        // Compare with each Available Address
        for(j=0; j<numAvailable; j++) {

            // Obtain Binary Representation/Number of Bits of Available Address
            sscanf(availableAddresses[j], "%d.%d.%d.%d/%d", &octAvailable[0], &octAvailable[1], &octAvailable[2], &octAvailable[3], &nBits);
            transformBinary(octAvailable, binAvailableAddress);

            // Compare Binary
            success = 1;
            for(k=0; k<nBits; k++) {
                if(binTestAddress[k] != binAvailableAddress[k]) {
                    success = 0;
                    break;
                }
            }

            // Determine how Specific
            if(success && nBits > bestRange) {
                bestIndex = j;
                bestRange = nBits;
            }
        }

        // Print Results
        if(bestIndex == -1) {
            // If an appropriate address hasn't been found
            sscanf(testAddresses[i], "%d.%d.%d.%d", &val1, &val2, &val3, &val4);
            printf("%d.%d.%d.%d N/A\n", val1, val2, val3, val4);
        } else {
            // If there is a specific address
            sscanf(availableAddresses[bestIndex], "%d.%d.%d.%d/%d %s", &val1, &val2, &val3, &val4, &valBits, local);
            sscanf(testAddresses[i], "%d.%d.%d.%d", &val1, &val2, &val3, &val4);
            printf("%d.%d.%d.%d %s\n", val1, val2, val3, val4, local);
        }
    }

    return 0;
}