#include <stdio.h>

// Structure to represent a term in a sparse matrix
struct Term {
    int row;
    int col;
    int value;
};

// Function to read a sparse matrix from the user
void readSparseMatrix(struct Term matrix[], int *rows, int *cols, int *numTerms) {
    int i;
    printf("Enter the number of rows, columns, and non-zero terms: ");
    scanf("%d %d %d", rows, cols, numTerms);
    printf("Enter the terms (row, column, value):\n");
    for (i = 0; i < *numTerms; i++) {
        scanf("%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    }
}

// Function to print a sparse matrix
void printSparseMatrix(struct Term matrix[], int rows, int cols, int numTerms) {
    int i, j, k = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (k < numTerms && matrix[k].row == i && matrix[k].col == j) {
                printf("%d ", matrix[k++].value);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// Function to find the transpose of a sparse matrix
void transposeSparseMatrix(struct Term matrix[], struct Term transpose[], int numTerms) {
    int i, j, k = 0;
    int rows = matrix[0].row;
    int cols = matrix[0].col;

    transpose[0].row = cols;
    transpose[0].col = rows;
    transpose[0].value = numTerms;

    if (numTerms > 0) {
        for (i = 0; i < cols; i++) {
            for (j = 0; j < numTerms; j++) {
                if (matrix[j+1].col == i) {
                    transpose[k+1].row = matrix[j+1].col;
                    transpose[k+1].col = matrix[j+1].row;
                    transpose[k+1].value = matrix[j+1].value;
                    k++;
                }
            }
        }
    }
}

// Function to add two sparse matrices
int addSparseMatrices(struct Term m1[], int n1, struct Term m2[], int n2, struct Term result[]) {
    int i = 0, j = 0, k = 0;

    if (m1[0].row != m2[0].row || m1[0].col != m2[0].col) {
        return -1; // Matrices have different dimensions
    }

    result[0].row = m1[0].row;
    result[0].col = m1[0].col;

    while (i < n1 && j < n2) {
        if (m1[i+1].row < m2[j+1].row || (m1[i+1].row == m2[j+1].row && m1[i+1].col < m2[j+1].col)) {
            result[k+1] = m1[i+1];
            i++;
        } else if (m1[i+1].row > m2[j+1].row || (m1[i+1].row == m2[j+1].row && m1[i+1].col > m2[j+1].col)) {
            result[k+1] = m2[j+1];
            j++;
        } else {
            result[k+1].row = m1[i+1].row;
            result[k+1].col = m1[i+1].col;
            result[k+1].value = m1[i+1].value + m2[j+1].value;
            i++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        result[k+1] = m1[i+1];
        i++;
        k++;
    }

    while (j < n2) {
        result[k+1] = m2[j+1];
        j++;
        k++;
    }

    result[0].value = k;
    return k;
}

int main() {
    struct Term matrix1[10], matrix2[10], result[20], transpose[10];
    int rows1, cols1, numTerms1, rows2, cols2, numTerms2, numTerms3;

    printf("Enter the first sparse matrix:\n");
    readSparseMatrix(matrix1, &rows1, &cols1, &numTerms1);

    printf("\nEnter the second sparse matrix:\n");
    readSparseMatrix(matrix2, &rows2, &cols2, &numTerms2);

    printf("\nFirst sparse matrix:\n");
    printSparseMatrix(matrix1, rows1, cols1, numTerms1);

    printf("\nSecond sparse matrix:\n");
    printSparseMatrix(matrix2, rows2, cols2, numTerms2);

    // Transpose
    transposeSparseMatrix(matrix1, transpose, numTerms1);
    printf("\nTranspose of the first matrix:\n");
    printSparseMatrix(transpose, cols1, rows1, numTerms1);

    // Addition
    numTerms3 = addSparseMatrices(matrix1, numTerms1, matrix2, numTerms2, result);
    if (numTerms3 != -1) {
        printf("\nSum of the two matrices:\n");
        printSparseMatrix(result, rows1, cols1, numTerms3);
    } else {
        printf("\nAddition not possible. Matrices have different dimensions.\n");
    }

    return 0;
}
