#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void testScalability();
void testParallelism();
void testHighShifts();
void testRandomDataset();

// Function to perform Insertion Sort and count swaps/shifts
int insertionSort(int arr[], int n) {
    int i, key, j, swaps = 0;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift elements
            j--;
            swaps++; // Count shifts
        }
        arr[j + 1] = key;
    }
    return swaps; // Return number of swaps/shifts
}

// Function to measure execution time
double measureExecutionTime(int arr[], int n, int *swaps) {
    clock_t start, end;
    start = clock();
    *swaps = insertionSort(arr, n);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Test scalability (Time Complexity)
void testScalability() {
    int smallSize = 1000, largeSize = 100000;
    int smallArr[smallSize], largeArr[largeSize];

    for (int i = 0; i < smallSize; i++) smallArr[i] = rand() % 10000;
    for (int i = 0; i < largeSize; i++) largeArr[i] = rand() % 10000;

    int swapsSmall, swapsLarge;
    double timeSmall = measureExecutionTime(smallArr, smallSize, &swapsSmall);
    double timeLarge = measureExecutionTime(largeArr, largeSize, &swapsLarge);

    printf("Testing Scalability:\n");
    printf("Sorting %d elements took %.6f seconds with %d swaps.\n", smallSize, timeSmall, swapsSmall);
    printf("Sorting %d elements took %.6f seconds with %d swaps.\n\n", largeSize, timeLarge, swapsLarge);

    printf("Explanation:\n");
    printf("Notice the drastic increase in execution time due to O(n²) complexity.\n");
    printf("As dataset size grows, Insertion Sort becomes increasingly inefficient.\n\n");
}

// Test limited parallelism
void testParallelism() {
    int unorderedSet[] = {30, 20, 50, 40, 10};
    int orderedSet[] = {10, 20, 30, 40, 50};

    int swapsUnordered, swapsOrdered;
    double timeUnordered = measureExecutionTime(unorderedSet, 5, &swapsUnordered);
    double timeOrdered = measureExecutionTime(orderedSet, 5, &swapsOrdered);

    printf("Testing Limited Parallelism:\n");
    printf("Unordered set: {30, 20, 50, 40, 10}\n");
    printf("Ordered set: {10, 20, 30, 40, 50}\n");
    printf("Sorting unordered set took %.6f seconds with %d swaps.\n", timeUnordered, swapsUnordered);
    printf("Sorting ordered set took %.6f seconds with %d swaps.\n\n", timeOrdered, swapsOrdered);

    printf("Explanation:\n");
    printf("Insertion Sort works sequentially, causing high swaps in unordered data.\n");
    printf("Sorted input has minimal swaps, but parallel optimization is still lacking.\n\n");
}

// Test high number of shifts
void testHighShifts() {
    int sortedArray[] = {10, 20, 30, 40, 50};
    int withInsertion[] = {10, 20, 30, 40, 50, 25}; // Inserted element

    int swapsBefore, shifts;
    measureExecutionTime(sortedArray, 5, &swapsBefore);
    shifts = insertionSort(withInsertion, 6); // Count shifts for inserted element

    printf("Testing High Number of Shifts:\n");
    printf("Sorted array before inserting new element: {10, 20, 30, 40, 50}\n");
    printf("Sorted array after inserting 25: {10, 20, 25, 30, 40, 50}\n");
    printf("Number of shifts when inserting 25: %d shifts.\n\n", shifts);

    printf("Explanation:\n");
    printf("Inserting a new element causes multiple elements to shift positions.\n");
    printf("For larger datasets, this results in excessive memory operations.\n\n");
}

// Function to generate random dataset
void generateRandomArray(int arr[], int n, int isNearlySorted) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Random numbers
    }
    if (isNearlySorted) {
        insertionSort(arr, n / 2); // Partially sort half to create an almost sorted dataset
    }
}

// Test random dataset swaps
void testRandomDataset() {
    int random5[5], sorted5[5], random20[20], sorted20[20];

    generateRandomArray(random5, 5, 0);  // Completely random
    generateRandomArray(sorted5, 5, 1);  // Nearly sorted
    generateRandomArray(random20, 20, 0);
    generateRandomArray(sorted20, 20, 1);

    int swapsRandom5, swapsSorted5, swapsRandom20, swapsSorted20;
    measureExecutionTime(random5, 5, &swapsRandom5);
    measureExecutionTime(sorted5, 5, &swapsSorted5);
    measureExecutionTime(random20, 20, &swapsRandom20);
    measureExecutionTime(sorted20, 20, &swapsSorted20);

    printf("Testing Random Dataset:\n");
    printf("Random 5-element dataset swaps: %d\n", swapsRandom5);
    printf("Almost sorted 5-element dataset swaps: %d\n", swapsSorted5);
    printf("Random 20-element dataset swaps: %d\n", swapsRandom20);
    printf("Almost sorted 20-element dataset swaps: %d\n\n", swapsSorted20);

    printf("Explanation:\n");
    printf("Random datasets require many swaps, while nearly sorted datasets are more efficient.\n");
    printf("The larger the dataset, the more Insertion Sort struggles.\n\n");
}

// Main menu
int main() {
    srand(time(NULL));  // Seed random number generator

    int choice;
    do {
        printf("Insertion Sort Limitation Tests:\n");
        printf("1. Test Scalability (Time Complexity)\n");
        printf("2. Test Limited Parallelism\n");
        printf("3. Test High Number of Shifts (Insert New Element)\n");
        printf("4. Test Random Dataset\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: testScalability(); break;
            case 2: testParallelism(); break;
            case 3: testHighShifts(); break;
            case 4: testRandomDataset(); break;
            case 5: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
