#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

// Structure to represent a non-zero element in a sparse matrix
struct Element {
    int row;
    int col;
    int value;
};

// Function to read a sparse matrix
void readSparseMatrix(struct Element matrix[], int* numRows, int* numCols, int* numTerms) {
    printf("Enter number of rows, columns, and non-zero terms: ");
    scanf("%d %d %d", numRows, numCols, numTerms);

    printf("Enter row, column, and value for each non-zero term:\n");
    for (int i = 0; i < *numTerms; i++) {
        scanf("%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    }
}

// Function to display a sparse matrix (in triplet form)
void displaySparseMatrix(struct Element matrix[], int numTerms) {
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < numTerms; i++) {
        printf("%d\t%d\t%d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }
}

// Function to transpose a sparse matrix
void transposeSparseMatrix(
    struct Element original[],
    int numTerms,
    struct Element transposed[],
    int numRows, // Original numRows becomes transposed numCols
    int numCols  // Original numCols becomes transposed numRows
) {
    int k = 0;
    for (int c = 0; c < numCols; c++) { // Iterate through original columns
        for (int i = 0; i < numTerms; i++) {
            if (original[i].col == c) {
                transposed[k].row = original[i].col;
                transposed[k].col = original[i].row;
                transposed[k].value = original[i].value;
                k++;
            }
        }
    }
}

// Function to add two sparse matrices
// Assumes matrices are sorted by row then column
void addSparseMatrices(
    struct Element matrix1[],
    int numTerms1,
    struct Element matrix2[],
    int numTerms2,
    struct Element result[],
    int* numTermsResult,
    int numRows, // Dimensions must match for addition
    int numCols
) {
    int i = 0, j = 0, k = 0;

    while (i < numTerms1 && j < numTerms2) {
        // Compare elements based on row and then column
        if (matrix1[i].row < matrix2[j].row || (matrix1[i].row == matrix2[j].row && matrix1[i].col < matrix2[j].col)) {
            result[k++] = matrix1[i++];
        } else if (matrix2[j].row < matrix1[i].row || (matrix2[j].row == matrix1[i].row && matrix2[j].col < matrix1[i].col)) {
            result[k++] = matrix2[j++];
        } else { // Elements are at the same position (same row and col)
            int sum = matrix1[i].value + matrix2[j].value;
            if (sum != 0) {
                result[k].row = matrix1[i].row;
                result[k].col = matrix1[i].col;
                result[k].value = sum;
                k++;
            }
            i++;
            j++;
        }
    }

    // Add remaining terms from matrix1
    while (i < numTerms1) {
        result[k++] = matrix1[i++];
    }

    // Add remaining terms from matrix2
    while (j < numTerms2) {
        result[k++] = matrix2[j++];
    }
    *numTermsResult = k;
}

int main() {
    struct Element matrix1[MAX_TERMS];
    struct Element matrix2[MAX_TERMS];
    struct Element transposedMatrix[MAX_TERMS];
    struct Element sumMatrix[MAX_TERMS];

    int numRows1, numCols1, numTerms1;
    int numRows2, numCols2, numTerms2;
    int numTermsTransposed = 0;
    int numTermsSum = 0;

    printf("\n--- Enter Matrix 1 ---\n");
    readSparseMatrix(matrix1, &numRows1, &numCols1, &numTerms1);
    printf("Matrix 1:\n");
    displaySparseMatrix(matrix1, numTerms1);

    printf("\n--- Transposing Matrix 1 ---\n");
    transposeSparseMatrix(matrix1, numTerms1, transposedMatrix, numRows1, numCols1);
    // The number of terms remains the same after transpose
    numTermsTransposed = numTerms1;
    printf("Transposed Matrix 1 (dimensions %dx%d):\n", numCols1, numRows1);
    displaySparseMatrix(transposedMatrix, numTermsTransposed);

    printf("\n--- Enter Matrix 2 (for addition) ---\n");
    readSparseMatrix(matrix2, &numRows2, &numCols2, &numTerms2);
    printf("Matrix 2:\n");
    displaySparseMatrix(matrix2, numTerms2);

    // Check if matrices can be added
    if (numRows1 != numRows2 || numCols1 != numCols2) {
        printf("\nError: Matrices dimensions do not match for addition.\n");
    } else {
        printf("\n--- Adding Matrix 1 and Matrix 2 ---\n");
        addSparseMatrices(matrix1, numTerms1, matrix2, numTerms2, sumMatrix, &numTermsSum, numRows1, numCols1);
        printf("Sum Matrix (dimensions %dx%d):\n", numRows1, numCols1);
        displaySparseMatrix(sumMatrix, numTermsSum);
    }

    return 0;
}
