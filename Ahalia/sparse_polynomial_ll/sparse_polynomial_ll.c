#include <stdio.h>
#include <stdlib.h>

// Structure for a term in the polynomial
struct TermNode {
    int coefficient;
    int exponent;
    struct TermNode* next;
};

// Function to create a new term node
struct TermNode* createTermNode(int coeff, int exp) {
    struct TermNode* newNode = (struct TermNode*)malloc(sizeof(struct TermNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into a polynomial (maintaining sorted order by exponent)
struct TermNode* insertTerm(
    struct TermNode* head,
    int coeff,
    int exp
) {
    if (coeff == 0) return head; // Don't insert zero coefficient terms

    struct TermNode* newNode = createTermNode(coeff, exp);

    // If list is empty or new term has higher exponent than head
    if (head == NULL || exp > head->exponent) {
        newNode->next = head;
        return newNode;
    }

    struct TermNode* current = head;
    struct TermNode* prev = NULL;

    while (current != NULL && exp <= current->exponent) {
        if (exp == current->exponent) {
            // If exponents are same, add coefficients
            current->coefficient += coeff;
            if (current->coefficient == 0) {
                // If sum becomes zero, remove the node
                if (prev == NULL) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                free(newNode); // Free the unused new node
                return head;
            }
            free(newNode); // Free the unused new node
            return head;
        }
        prev = current;
        current = current->next;
    }

    // Insert newNode between prev and current
    newNode->next = current;
    if (prev != NULL) {
        prev->next = newNode;
    } else {
        // This case should ideally be handled by the first if condition
        // if exp > head->exponent, but as a fallback.
        head = newNode;
    }
    return head;
}

// Function to display a polynomial
void displayPolynomial(struct TermNode* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct TermNode* current = head;
    while (current != NULL) {
        printf("%dx^%d", current->coefficient, current->exponent);
        current = current->next;
        if (current != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
struct TermNode* addPolynomials(
    struct TermNode* poly1,
    struct TermNode* poly2
) {
    struct TermNode* result = NULL;
    struct TermNode* current1 = poly1;
    struct TermNode* current2 = poly2;

    while (current1 != NULL || current2 != NULL) {
        if (current1 == NULL) {
            result = insertTerm(result, current2->coefficient, current2->exponent);
            current2 = current2->next;
        } else if (current2 == NULL) {
            result = insertTerm(result, current1->coefficient, current1->exponent);
            current1 = current1->next;
        } else if (current1->exponent == current2->exponent) {
            result = insertTerm(
                result,
                current1->coefficient + current2->coefficient,
                current1->exponent
            );
            current1 = current1->next;
            current2 = current2->next;
        } else if (current1->exponent > current2->exponent) {
            result = insertTerm(result, current1->coefficient, current1->exponent);
            current1 = current1->next;
        } else { // current2->exponent > current1->exponent
            result = insertTerm(result, current2->coefficient, current2->exponent);
            current2 = current2->next;
        }
    }
    return result;
}

// Function to multiply two polynomials
struct TermNode* multiplyPolynomials(
    struct TermNode* poly1,
    struct TermNode* poly2
) {
    struct TermNode* result = NULL;
    struct TermNode* current1 = poly1;

    if (poly1 == NULL || poly2 == NULL) return NULL;

    while (current1 != NULL) {
        struct TermNode* current2 = poly2;
        struct TermNode* temp_poly = NULL;
        while (current2 != NULL) {
            int coeff = current1->coefficient * current2->coefficient;
            int exp = current1->exponent + current2->exponent;
            temp_poly = insertTerm(temp_poly, coeff, exp);
            current2 = current2->next;
        }
        // Add temp_poly to the result polynomial
        result = addPolynomials(result, temp_poly);
        // Free temp_poly nodes after adding
        struct TermNode* to_free = temp_poly;
        while(to_free != NULL) {
            struct TermNode* next_to_free = to_free->next;
            free(to_free);
            to_free = next_to_free;
        }
        current1 = current1->next;
    }
    return result;
}

// Function to free the memory allocated for a polynomial linked list
void freePolynomial(struct TermNode* head) {
    struct TermNode* current = head;
    while (current != NULL) {
        struct TermNode* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct TermNode* poly1 = NULL;
    struct TermNode* poly2 = NULL;
    struct TermNode* polySum = NULL;
    struct TermNode* polyProduct = NULL;

    // Create Polynomial 1: 5x^2 + 2x^1 + 4x^0
    poly1 = insertTerm(poly1, 5, 2);
    poly1 = insertTerm(poly1, 2, 1);
    poly1 = insertTerm(poly1, 4, 0);

    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    // Create Polynomial 2: 3x^2 + 1x^1 + 7x^0
    poly2 = insertTerm(poly2, 3, 2);
    poly2 = insertTerm(poly2, 1, 1);
    poly2 = insertTerm(poly2, 7, 0);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Add polynomials
    polySum = addPolynomials(poly1, poly2);
    printf("Sum of Polynomials: ");
    displayPolynomial(polySum);

    // Multiply polynomials
    polyProduct = multiplyPolynomials(poly1, poly2);
    printf("Product of Polynomials: ");
    displayPolynomial(polyProduct);

    // Free allocated memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(polySum);
    freePolynomial(polyProduct);

    return 0;
}
