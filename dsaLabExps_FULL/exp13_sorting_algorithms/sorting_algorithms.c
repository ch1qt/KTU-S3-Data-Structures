#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global counters for comparisons and assignments/swaps
long long comparisons = 0;
long long assignments = 0;

// Helper function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    assignments += 3; // 3 assignments for a swap
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    comparisons = 0;
    assignments = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    printf("Bubble Sort: Comparisons = %lld, Assignments/Swaps = %lld\n", comparisons, assignments);
}

// 2. Insertion Sort
void insertionSort(int arr[], int n) {
    comparisons = 0;
    assignments = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        assignments++;
        int j = i - 1;
        while (j >= 0) {
            comparisons++; // Comparison arr[j] > key
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                assignments++;
                j = j - 1;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        assignments++;
    }
    printf("Insertion Sort: Comparisons = %lld, Assignments = %lld\n", comparisons, assignments);
}

// 3. Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    assignments++;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void runQuickSort(int arr[], int n) {
    comparisons = 0;
    assignments = 0;
    quickSort(arr, 0, n - 1);
    printf("Quick Sort: Comparisons = %lld, Assignments/Swaps = %lld\n", comparisons, assignments);
}

// 4. Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        assignments++;
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        assignments++;
    }

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        assignments++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        assignments++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        assignments++;
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void runMergeSort(int arr[], int n) {
    comparisons = 0;
    assignments = 0;
    mergeSort(arr, 0, n - 1);
    printf("Merge Sort: Comparisons = %lld, Assignments = %lld\n", comparisons, assignments);
}

// 5. Radix Sort (LSD Radix Sort)
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        comparisons++;
        if (arr[i] > max) {
            max = arr[i];
            assignments++;
        }
    }
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};
    assignments += n; // For output array
    assignments += 10; // For count array

    for (i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
        assignments++;
    }

    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
        assignments++;
    }

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        assignments++;
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++) {
        arr[i] = output[i];
        assignments++;
    }
}

void radixSort(int arr[], int n) {
    comparisons = 0;
    assignments = 0;
    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
    printf("Radix Sort: Comparisons = %lld, Assignments = %lld\n", comparisons, assignments);
}

int main() {
    int arr_bubble[] = {64, 34, 25, 12, 22, 11, 90};
    int arr_insertion[] = {64, 34, 25, 12, 22, 11, 90};
    int arr_quick[] = {64, 34, 25, 12, 22, 11, 90};
    int arr_merge[] = {64, 34, 25, 12, 22, 11, 90};
    int arr_radix[] = {170, 45, 75, 90, 802, 24, 2, 66};

    int n_bubble = sizeof(arr_bubble) / sizeof(arr_bubble[0]);
    int n_insertion = sizeof(arr_insertion) / sizeof(arr_insertion[0]);
    int n_quick = sizeof(arr_quick) / sizeof(arr_quick[0]);
    int n_merge = sizeof(arr_merge) / sizeof(arr_merge[0]);
    int n_radix = sizeof(arr_radix) / sizeof(arr_radix[0]);

    printf("Original Array (for Bubble, Insertion, Quick, Merge): ");
    printArray(arr_bubble, n_bubble);
    printf("Original Array (for Radix): ");
    printArray(arr_radix, n_radix);
    printf("\n");

    printf("Running Bubble Sort...\n");
    bubbleSort(arr_bubble, n_bubble);
    printf("Sorted array: ");
    printArray(arr_bubble, n_bubble);
    printf("\n");

    printf("Running Insertion Sort...\n");
    insertionSort(arr_insertion, n_insertion);
    printf("Sorted array: ");
    printArray(arr_insertion, n_insertion);
    printf("\n");

    printf("Running Quick Sort...\n");
    runQuickSort(arr_quick, n_quick);
    printf("Sorted array: ");
    printArray(arr_quick, n_quick);
    printf("\n");

    printf("Running Merge Sort...\n");
    runMergeSort(arr_merge, n_merge);
    printf("Sorted array: ");
    printArray(arr_merge, n_merge);
    printf("\n");

    printf("Running Radix Sort...\n");
    radixSort(arr_radix, n_radix);
    printf("Sorted array: ");
    printArray(arr_radix, n_radix);
    printf("\n");

    return 0;
}
