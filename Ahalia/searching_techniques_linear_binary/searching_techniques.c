#include <stdio.h>

// Function for Linear Search
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // Return the index if target is found
        }
    }
    return -1; // Return -1 if target is not found
}

// Function for Binary Search (requires a sorted array)
int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2; // To prevent potential overflow

        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If target is greater, ignore left half
        if (arr[mid] < target) {
            low = mid + 1;
        }
        // If target is smaller, ignore right half
        else {
            high = mid - 1;
        }
    }
    return -1; // Return -1 if target is not found
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target;
    int result;

    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Linear Search
    target = 16;
    result = linearSearch(arr, n, target);
    if (result != -1) {
        printf("Linear Search: Element %d found at index %d.\n", target, result);
    } else {
        printf("Linear Search: Element %d not found in the array.\n", target);
    }

    target = 100;
    result = linearSearch(arr, n, target);
    if (result != -1) {
        printf("Linear Search: Element %d found at index %d.\n", target, result);
    } else {
        printf("Linear Search: Element %d not found in the array.\n", target);
    }

    printf("\n");

    // Binary Search (array must be sorted)
    target = 23;
    result = binarySearch(arr, 0, n - 1, target);
    if (result != -1) {
        printf("Binary Search: Element %d found at index %d.\n", target, result);
    } else {
        printf("Binary Search: Element %d not found in the array.\n", target);
    }

    target = 1;
    result = binarySearch(arr, 0, n - 1, target);
    if (result != -1) {
        printf("Binary Search: Element %d found at index %d.\n", target, result);
    } else {
        printf("Binary Search: Element %d not found in the array.\n", target);
    }

    return 0;
}
