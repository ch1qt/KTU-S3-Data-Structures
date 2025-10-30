#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort (to sort in descending order)
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// Function to find the maximum activity points
int maxActivityPoints(int A[], int n, int k) {
    // Sort the array in descending order
    qsort(A, n, sizeof(int), compare);

    int max_points = 0;
    // Sum the top k activity points
    for (int i = 0; i < k && i < n; i++) {
        max_points += A[i];
    }
    return max_points;
}

int main() {
    int A[] = {10, 5, 20, 8, 15};
    int n = sizeof(A) / sizeof(A[0]);
    int k = 3;

    printf("Activity points available: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("Maximum number of events to participate in: %d\n", k);

    int max_points = maxActivityPoints(A, n, k);

    printf("Maximum activity points that can be earned: %d\n", max_points);

    return 0;
}
