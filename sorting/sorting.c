#include <stdio.h>
#include <stdlib.h>

void swap(int *numbers, int first, int second) {
    int temp;
    temp = numbers[first];
    numbers[first] = numbers[second];
    numbers[second] = temp;
}

void quickSort(int *numbers, int start, int end) {
    int pivot;
    int countGeneral;
    int countAuxiliary = start - 1;
    int quantNumbers = (end-start) + 1;

    // Randomly select Pivot
    pivot = (rand() % quantNumbers) + start;
    swap(numbers, end, pivot);

    // Moving Positions
    for(countGeneral = start; countGeneral < end; countGeneral++) {
        if(numbers[countGeneral] < numbers[end]) {
            countAuxiliary++;
            swap(numbers, countGeneral, countAuxiliary);
        }
    }

    // Readjust pivot
    pivot = countAuxiliary + 1;
    swap(numbers, countAuxiliary + 1, end);

    // Order Remaining Segments
    if((end-start) != 0) {
        if(pivot != start) {
            quickSort(numbers, start, pivot - 1);
        }
        if(pivot != end) {
            quickSort(numbers, pivot + 1, end);
        }
    }
}

int* mergeSort(int *numbers, int start, int end) {
    // General Variables
    int midpoint = ((end-start)/2) + start;
    int quantNumbers = (end - start) + 1;
    int countGeneral, countLeft, countRight;

    // Ordered Number Vectors
    int *orderedNumbers;
    int *left;
    int *right;
    orderedNumbers = (int *) malloc(quantNumbers*sizeof(int));

    // When there is only one element
    if(quantNumbers <= 1) {
        orderedNumbers[0] = numbers[start];
        return orderedNumbers;
    }
    else {
        // Split
        left = mergeSort(numbers, start, midpoint);
        right = mergeSort(numbers, midpoint+1, end);

        // Segment Indices
        countGeneral = 0;
        countLeft = 0;
        countRight = 0;

        // Join Segments
        while(countLeft <= (midpoint-start) && countRight < (end-midpoint)) {
            if(left[countLeft] < right[countRight]) {
                // If left number smaller
                orderedNumbers[countGeneral] = left[countLeft];
                countLeft++;
            }
            else {
                // If right number smaller
                orderedNumbers[countGeneral] = right[countRight];
                countRight++;
            }

            // Update Counter
            countGeneral++;
        }

        // In Case Right Vector Over
        while(countLeft <= (midpoint-start)) {
            orderedNumbers[countGeneral] = left[countLeft];
            countLeft++;
            countGeneral++;
        }

        // In Case Left Vector Over
        while(countRight < (end-midpoint)) {
            orderedNumbers[countGeneral] = right[countRight];
            countRight++;
            countGeneral++;
        }
    }
    return orderedNumbers;
}

int main(int argc, char *argv[]) {
    // General Variables
    int *numbers;
    int quantNumbers;
    int i;

    if(argc != 2) {
        // Print error if arguments insufficient
        printf("Error! Sorting algorithm not selected. Available algorithms: \n\n * Merge Sort: -m\n * Quick Sort: -q\n");
    } else {

        // Read Amount of Numbers
        scanf("%d", &quantNumbers);

        // Allocate Memory
        numbers = (int *) malloc(quantNumbers * sizeof(int));

        // Read Numbers
        for(i=0; i<quantNumbers; i++) {
            scanf("%d", &numbers[i]);
        }

        // Sort with Merge Sort
        if(argv[1][1] = "m") {
            numbers == mergeSort(numbers,0, quantNumbers-1);
        }

        // Sort with Quick Sort
        if(argv[1][1] = "q") {
            quickSort(numbers, 0, quantNumbers - 1);
        }

        // Print Results
        for(i=0; i<quantNumbers; i++) {
            printf("%d\n", numbers[i]);
        }
    }

    return 0;
}