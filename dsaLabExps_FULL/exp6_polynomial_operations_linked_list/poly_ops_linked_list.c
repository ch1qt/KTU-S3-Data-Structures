#include <stdio.h>
#include <stdlib.h>

// Structure for a polynomial term
struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into a polynomial (sorted by exponent in descending order)
struct Node* insertTerm(struct Node* head, int coeff, int exp) {
    if (coeff == 0) return head;

    struct Node* newNode = createNode(coeff, exp);

    if (head == NULL || exp > head->exponent) {
        newNode->next = head;
        return newNode;
    }

    struct Node* current = head;
    while (current->next != NULL && exp < current->next->exponent) {
        current = current->next;
    }

    if (current->next != NULL && exp == current->next->exponent) {
        current->next->coefficient += coeff;
        if (current->next->coefficient == 0) {
            struct Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        }
        free(newNode); // New node not needed if merged
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

// Function to read a polynomial from the user
struct Node* readPolynomial() {
    struct Node* head = NULL;
    int numTerms, coeff, exp, i;
    printf("Enter the number of terms: ");
    scanf("%d", &numTerms);
    printf("Enter coefficient and exponent for each term:\n");
    for (i = 0; i < numTerms; i++) {
        scanf("%d %d", &coeff, &exp);
        head = insertTerm(head, coeff, exp);
    }
    return head;
}

// Function to print a polynomial
void printPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* current = head;
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
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* ptr1 = poly1;
    struct Node* ptr2 = poly2;

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->exponent > ptr2->exponent) {
            result = insertTerm(result, ptr1->coefficient, ptr1->exponent);
            ptr1 = ptr1->next;
        } else if (ptr2->exponent > ptr1->exponent) {
            result = insertTerm(result, ptr2->coefficient, ptr2->exponent);
            ptr2 = ptr2->next;
        } else {
            int sumCoeff = ptr1->coefficient + ptr2->coefficient;
            if (sumCoeff != 0) {
                result = insertTerm(result, sumCoeff, ptr1->exponent);
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    while (ptr1 != NULL) {
        result = insertTerm(result, ptr1->coefficient, ptr1->exponent);
        ptr1 = ptr1->next;
    }

    while (ptr2 != NULL) {
        result = insertTerm(result, ptr2->coefficient, ptr2->exponent);
        ptr2 = ptr2->next;
    }
    return result;
}

// Function to multiply two polynomials
struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    if (poly1 == NULL || poly2 == NULL) {
        return NULL;
    }

    struct Node* ptr1 = poly1;
    while (ptr1 != NULL) {
        struct Node* ptr2 = poly2;
        while (ptr2 != NULL) {
            int coeff = ptr1->coefficient * ptr2->coefficient;
            int exp = ptr1->exponent + ptr2->exponent;
            result = insertTerm(result, coeff, exp);
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return result;
}

// Function to free the memory allocated for a polynomial
void freePolynomial(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* sum = NULL;
    struct Node* product = NULL;

    printf("Enter first polynomial:\n");
    poly1 = readPolynomial();

    printf("Enter second polynomial:\n");
    poly2 = readPolynomial();

    printf("\nPolynomial 1: ");
    printPolynomial(poly1);

    printf("Polynomial 2: ");
    printPolynomial(poly2);

    sum = addPolynomials(poly1, poly2);
    printf("Sum: ");
    printPolynomial(sum);

    product = multiplyPolynomials(poly1, poly2);
    printf("Product: ");
    printPolynomial(product);

    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(sum);
    freePolynomial(product);

    return 0;
}
