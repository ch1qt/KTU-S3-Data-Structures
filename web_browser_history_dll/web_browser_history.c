#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 100

// Structure for a page node in the doubly linked list
struct PageNode {
    char url[MAX_URL_LENGTH];
    struct PageNode* prev;
    struct PageNode* next;
};

// Global pointer to the current page
struct PageNode* currentPage = NULL;

// Function to create a new page node
struct PageNode* createPageNode(const char* url) {
    struct PageNode* newNode = (struct PageNode*)malloc(sizeof(struct PageNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strncpy(newNode->url, url, MAX_URL_LENGTH - 1);
    newNode->url[MAX_URL_LENGTH - 1] = '\0'; // Ensure null-termination
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to free forward history (pages ahead of current)
void freeForwardHistory(struct PageNode* startNode) {
    if (startNode == NULL) return;

    struct PageNode* current = startNode->next;
    while (current != NULL) {
        struct PageNode* temp = current;
        current = current->next;
        free(temp);
    }
    startNode->next = NULL;
}

// Function to visit a new page
void visitPage(const char* url) {
    struct PageNode* newNode = createPageNode(url);

    if (currentPage == NULL) {
        currentPage = newNode;
    } else {
        // Clear any forward history before adding a new page
        freeForwardHistory(currentPage);

        newNode->prev = currentPage;
        currentPage->next = newNode;
        currentPage = newNode;
    }
    printf("Visited: %s\n", currentPage->url);
}

// Function to go back to the previous page
void goBack() {
    if (currentPage == NULL || currentPage->prev == NULL) {
        printf("Cannot go back. No previous page.\n");
    } else {
        currentPage = currentPage->prev;
        printf("Went back to: %s\n", currentPage->url);
    }
}

// Function to go forward to the next page
void goForward() {
    if (currentPage == NULL || currentPage->next == NULL) {
        printf("Cannot go forward. No next page.\n");
    } else {
        currentPage = currentPage->next;
        printf("Went forward to: %s\n", currentPage->url);
    }
}

// Function to display the current page
void displayCurrentPage() {
    if (currentPage == NULL) {
        printf("No page visited yet.\n");
    } else {
        printf("Current Page: %s\n", currentPage->url);
    }
}

// Function to display the entire history (for debugging/demonstration)
void displayHistory() {
    if (currentPage == NULL) {
        printf("History is empty.\n");
        return;
    }

    // Find the very first page
    struct PageNode* temp = currentPage;
    while (temp->prev != NULL) {
        temp = temp->prev;
    }

    printf("\n--- Browsing History ---\n");
    while (temp != NULL) {
        printf("%s %s\n", temp->url, (temp == currentPage ? "(Current)" : ""));
        temp = temp->next;
    }
    printf("----------------------\n");
}

// Function to free all allocated memory for the history
void freeHistory() {
    if (currentPage == NULL) return;

    // Go to the very first page
    while (currentPage->prev != NULL) {
        currentPage = currentPage->prev;
    }

    // Free all nodes from start to end
    struct PageNode* current = currentPage;
    while (current != NULL) {
        struct PageNode* temp = current;
        current = current->next;
        free(temp);
    }
    currentPage = NULL;
    printf("Browser history cleared.\n");
}

int main() {
    displayCurrentPage();
    displayHistory();

    visitPage("google.com");
    visitPage("youtube.com");
    visitPage("gemini.google.com");
    displayHistory();

    goBack();
    goBack();
    displayCurrentPage();
    displayHistory();

    goForward();
    displayCurrentPage();
    displayHistory();

    visitPage("github.com"); // This should clear forward history (gemini.google.com)
    displayHistory();

    goForward(); // Should not be able to go forward
    goBack();
    displayHistory();

    freeHistory();
    displayHistory();

    return 0;
}
