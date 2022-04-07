/**
 * @author René García Avilés, Halle Countryman
 * @brief Buggy quick sort implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quickSort(int arr[], int first, int last);
void setArr(int arr[], int size);
void printArr(int arr[], int size);

int main(void) {
    int size;     
    printf("Array size: ");
    scanf("%d", &size);

    int* arr = malloc(sizeof(int) * size);
    setArr(arr, size);

    quickSort(arr, 0, size - 1);

    printf("\nOrdered array: \n");
    printArr(arr, size);

    return EXIT_SUCCESS;
}

/**
 * @brief Gather user input and fill in an array
 * 
 * @param arr array to fill
 * @param size size of arr
 */
void setArr(int arr[], int size) {
    for(size_t i = 0; i < size; i++) {
        printf("Assign to pos %zu: ", i);
        scanf("%d", &arr[i]);
    }
}

/**
 * @brief Print an array
 * 
 * @param arr array to print
 * @param size size of arr
 */
void printArr(int arr[], int size) {
    for(size_t i = 0; i < size; i++) {
        printf("Value at %zu -> %d\n", i, arr[i]);
    }
}

/**
 * @brief Quick sort: Pick pivot, put it where it goes (such that all smaller
 * elements are on its left and all larger ones on its right), sort everything
 * that comes before it (using quicksort), then finally sort everything that
 * comes after it (using quicksort).
 *
 * @param arr array to sort
 * @param first index to start sorting from (inclusive)
 * @param last index to stop sorting at (inclusive)
 */
void quickSort(int arr[], int first, int last) {
    int pivot = arr[last]; // Pivot is last value
    int temp;
    int j = first - 1; // Index as we iterate along array

    // Put everything smaller left of the pivot
    for(size_t i = first; i < last; i++) { // For each element
        if(arr[i] < pivot) { // If it is smaller than pivot
            j++; // Increment index to place smaller element at

            // Interchange so smaller element is at index j
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }

    // Interchange pivot with element at index j+1
    temp = arr[j + 1];
    arr[j + 1] = arr[last];
    arr[last] = temp;

    j++; // Increment j to get index of pivot

    // Recursively sort on either side of pivot:
    quickSort(arr, first, j - 1); // First half up to right before pivot
    quickSort(arr, j + 1, last); // Latter half, starting right after pivot
}
