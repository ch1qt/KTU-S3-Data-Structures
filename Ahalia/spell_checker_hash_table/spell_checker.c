#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DICTIONARY_SIZE 100
#define MAX_WORD_LENGTH 50

// Structure for a dictionary entry (linked list for collision handling)
typedef struct Node {
    char word[MAX_WORD_LENGTH];
    struct Node* next;
} Node;

// Hash Table (array of pointers to Nodes)
Node* hashTable[DICTIONARY_SIZE];

// Simple hash function
unsigned int hash(const char* word) {
    unsigned int hashValue = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hashValue = hashValue * 31 + word[i];
    }
    return hashValue % DICTIONARY_SIZE;
}

// Function to insert a word into the hash table
void insertWord(const char* word) {
    unsigned int index = hash(word);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->word, word);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Function to check if a word exists in the dictionary
bool checkWord(const char* word) {
    unsigned int index = hash(word);
    Node* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to generate and print suggestions (basic: single character deletion)
void generateSuggestions(const char* misspelledWord) {
    printf("Did you mean:\n");
    int len = strlen(misspelledWord);
    char tempWord[MAX_WORD_LENGTH];
    bool foundSuggestion = false;

    // Suggestion 1: Single character deletion
    for (int i = 0; i < len; i++) {
        int k = 0;
        for (int j = 0; j < len; j++) {
            if (i == j) continue;
            tempWord[k++] = misspelledWord[j];
        }
        tempWord[k] = '\0';
        if (checkWord(tempWord)) {
            printf("- %s\n", tempWord);
            foundSuggestion = true;
        }
    }

    // Suggestion 2: Single character substitution
    for (int i = 0; i < len; i++) {
        char originalChar = misspelledWord[i];
        for (char c = 'a'; c <= 'z'; c++) {
            strcpy(tempWord, misspelledWord);
            tempWord[i] = c;
            if (checkWord(tempWord) && strcmp(tempWord, misspelledWord) != 0) {
                printf("- %s\n", tempWord);
                foundSuggestion = true;
            }
        }
        tempWord[i] = originalChar; // Restore original character
    }

    if (!foundSuggestion) {
        printf("No suggestions found.\n");
    }
}

// Function to initialize the hash table
void initHashTable() {
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// Function to free memory used by the hash table
void freeHashTable() {
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    initHashTable();

    // Populate dictionary with some words
    insertWord("apple");
    insertWord("banana");
    insertWord("orange");
    insertWord("grape");
    insertWord("program");
    insertWord("programming");
    insertWord("computer");
    insertWord("science");

    char wordToCheck[MAX_WORD_LENGTH];

    printf("Enter a word to check (type 'exit' to quit): ");
    while (scanf("%s", wordToCheck) == 1 && strcmp(wordToCheck, "exit") != 0) {
        if (checkWord(wordToCheck)) {
            printf("'%s' is spelled correctly.\n", wordToCheck);
        } else {
            printf("'%s' is misspelled.\n", wordToCheck);
            generateSuggestions(wordToCheck);
        }
        printf("\nEnter a word to check (type 'exit' to quit): ");
    }

    freeHashTable();
    return 0;
}
