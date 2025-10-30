#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the doubly linked list
struct Node {
    char url[100];
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(char* url) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->url, url);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to visit a new page
void visitPage(struct Node** currentPage, char* url) {
    struct Node* newNode = createNode(url);
    if (*currentPage == NULL) {
        *currentPage = newNode;
    } else {
        // Clear forward history
        struct Node* temp = (*currentPage)->next;
        while (temp != NULL) {
            struct Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        (*currentPage)->next = newNode;
        newNode->prev = *currentPage;
        *currentPage = newNode;
    }
    printf("Visited: %s\n", url);
}

// Function to go back
void goBack(struct Node** currentPage) {
    if (*currentPage != NULL && (*currentPage)->prev != NULL) {
        *currentPage = (*currentPage)->prev;
        printf("Current Page: %s\n", (*currentPage)->url);
    } else {
        printf("No backward history.\n");
    }
}

// Function to go forward
void goForward(struct Node** currentPage) {
    if (*currentPage != NULL && (*currentPage)->next != NULL) {
        *currentPage = (*currentPage)->next;
        printf("Current Page: %s\n", (*currentPage)->url);
    } else {
        printf("No forward history.\n");
    }
}

int main() {
    struct Node* currentPage = NULL;

    visitPage(&currentPage, "google.com");
    visitPage(&currentPage, "facebook.com");
    visitPage(&currentPage, "youtube.com");

    goBack(&currentPage);
    goBack(&currentPage);

    goForward(&currentPage);

    visitPage(&currentPage, "linkedin.com");
    goForward(&currentPage);

    return 0;
}
