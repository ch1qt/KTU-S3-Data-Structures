#include <stdio.h>

// Iterative Binary Search
int binarySearchIterative(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // To prevent potential overflow

        if (arr[mid] == target) {
            return mid; // Target found
        } else if (arr[mid] < target) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }
    return -1; // Target not found
}

// Recursive Binary Search
int binarySearchRecursive(int arr[], int low, int high, int target) {
    if (low > high) {
        return -1; // Base case: Target not found
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] == target) {
        return mid; // Target found
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, high, target); // Search in right half
    } else {
        return binarySearchRecursive(arr, low, mid - 1, target); // Search in left half
    }
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target1 = 23;
    int target2 = 72;
    int target3 = 10;

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Test Iterative Binary Search
    int index1 = binarySearchIterative(arr, size, target1);
    if (index1 != -1) {
        printf("Iterative: %d found at index %d\n", target1, index1);
    } else {
        printf("Iterative: %d not found\n", target1);
    }

    int index2 = binarySearchIterative(arr, size, target3);
    if (index2 != -1) {
        printf("Iterative: %d found at index %d\n", target3, index2);
    } else {
        printf("Iterative: %d not found\n", target3);
    }

    printf("\n");

    // Test Recursive Binary Search
    int index3 = binarySearchRecursive(arr, 0, size - 1, target2);
    if (index3 != -1) {
        printf("Recursive: %d found at index %d\n", target2, index3);
    } else {
        printf("Recursive: %d not found\n", target2);
    }

    int index4 = binarySearchRecursive(arr, 0, size - 1, target3);
    if (index4 != -1) {
        printf("Recursive: %d found at index %d\n", target3, index4);
    } else {
        printf("Recursive: %d not found\n", target3);
    }

    return 0;
}
