#include <stdio.h>

// Structure to represent a term in a polynomial
struct Term {
    int coefficient;
    int exponent;
};

// Function to read a polynomial from the user
int readPolynomial(struct Term poly[]) {
    int n, i;
    printf("Enter the number of terms: ");
    scanf("%d", &n);
    printf("Enter the terms (coefficient and exponent):\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &poly[i].coefficient, &poly[i].exponent);
    }
    return n;
}

// Function to print a polynomial
void printPolynomial(struct Term poly[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%dx^%d", poly[i].coefficient, poly[i].exponent);
        if (i < n - 1) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
int addPolynomials(struct Term poly1[], int n1, struct Term poly2[], int n2, struct Term result[]) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (poly1[i].exponent > poly2[j].exponent) {
            result[k++] = poly1[i++];
        } else if (poly1[i].exponent < poly2[j].exponent) {
            result[k++] = poly2[j++];
        } else {
            result[k].exponent = poly1[i].exponent;
            result[k].coefficient = poly1[i].coefficient + poly2[j].coefficient;
            if (result[k].coefficient != 0) {
                k++;
            }
            i++;
            j++;
        }
    }

    // Copy remaining terms from poly1
    while (i < n1) {
        result[k++] = poly1[i++];
    }

    // Copy remaining terms from poly2
    while (j < n2) {
        result[k++] = poly2[j++];
    }

    return k;
}

int main() {
    struct Term poly1[10], poly2[10], result[20];
    int n1, n2, n3;

    printf("Enter the first polynomial:\n");
    n1 = readPolynomial(poly1);

    printf("\nEnter the second polynomial:\n");
    n2 = readPolynomial(poly2);

    n3 = addPolynomials(poly1, n1, poly2, n2, result);

    printf("\nFirst polynomial: ");
    printPolynomial(poly1, n1);

    printf("Second polynomial: ");
    printPolynomial(poly2, n2);

    printf("Resultant polynomial: ");
    printPolynomial(result, n3);

    return 0;
}
