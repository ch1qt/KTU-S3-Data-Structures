#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in a polynomial
struct Term {
    int coefficient;
    int exponent;
};

// Function to add two sparse polynomials
void addSparsePolynomials(
    struct Term poly1[],
    int n1,
    struct Term poly2[],
    int n2,
    struct Term result[],
    int* n3
) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (poly1[i].exponent > poly2[j].exponent) {
            result[k] = poly1[i];
            i++;
        } else if (poly2[j].exponent > poly1[i].exponent) {
            result[k] = poly2[j];
            j++;
        } else {
            // Exponents are equal, add coefficients
            result[k].coefficient = poly1[i].coefficient + poly2[j].coefficient;
            result[k].exponent = poly1[i].exponent;
            i++;
            j++;
        }
        // Only increment k if the resulting coefficient is not zero
        if (result[k].coefficient != 0) {
            k++;
        }
    }

    // Add remaining terms of poly1
    while (i < n1) {
        result[k] = poly1[i];
        i++;
        k++;
    }

    // Add remaining terms of poly2
    while (j < n2) {
        result[k] = poly2[j];
        j++;
        k++;
    }

    *n3 = k; // Update the size of the result polynomial
}

// Function to display a polynomial
void displayPolynomial(struct Term poly[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%dx^%d", poly[i].coefficient, poly[i].exponent);
        if (i < n - 1) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    // Example Usage
    struct Term poly1[] = {{5, 2}, {2, 1}, {4, 0}}; // 5x^2 + 2x^1 + 4x^0
    int n1 = sizeof(poly1) / sizeof(poly1[0]);

    struct Term poly2[] = {{3, 2}, {1, 1}, {7, 0}}; // 3x^2 + 1x^1 + 7x^0
    int n2 = sizeof(poly2) / sizeof(poly2[0]);

    // Maximum possible terms in the result is n1 + n2
    struct Term result[n1 + n2];
    int n3 = 0;

    printf("Polynomial 1: ");
    displayPolynomial(poly1, n1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2, n2);

    addSparsePolynomials(poly1, n1, poly2, n2, result, &n3);

    printf("Sum Polynomial: ");
    displayPolynomial(result, n3);

    return 0;
}
