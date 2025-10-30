#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 100
#define MAX_WORD_LEN 50

// Structure for a node in the linked list (for hash table chaining)
struct Node {
    char word[MAX_WORD_LEN];
    struct Node* next;
};

// Hash Table (array of linked lists)
struct Node* hashTable[TABLE_SIZE];

// Hash function (simple sum of ASCII values modulo table size)
unsigned int hash(const char* str) {
    unsigned int hash_val = 0;
    while (*str) {
        hash_val += *str;
        str++;
    }
    return hash_val % TABLE_SIZE;
}

// Function to insert a word into the hash table
void insertWord(const char* word) {
    unsigned int index = hash(word);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->word, word);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Function to search for a word in the hash table
bool searchWord(const char* word) {
    unsigned int index = hash(word);
    struct Node* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to check if a word is valid
bool checkWord(const char* word) {
    return searchWord(word);
}

// Function to suggest corrections for a misspelled word
void suggestCorrections(const char* misspelled_word) {
    printf("Suggestions for '%s':\n", misspelled_word);
    int word_len = strlen(misspelled_word);
    char temp_word[MAX_WORD_LEN];
    bool found_suggestion = false;

    // 1. Single character deletions
    for (int i = 0; i < word_len; i++) {
        int k = 0;
        for (int j = 0; j < word_len; j++) {
            if (i == j) continue;
            temp_word[k++] = misspelled_word[j];
        }
        temp_word[k] = '\0';
        if (checkWord(temp_word)) {
            printf("  - %s\n", temp_word);
            found_suggestion = true;
        }
    }

    // 2. Single character insertions
    for (int i = 0; i <= word_len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            int k = 0;
            for (int j = 0; j < i; j++) {
                temp_word[k++] = misspelled_word[j];
            }
            temp_word[k++] = c;
            for (int j = i; j < word_len; j++) {
                temp_word[k++] = misspelled_word[j];
            }
            temp_word[k] = '\0';
            if (checkWord(temp_word)) {
                printf("  - %s\n", temp_word);
                found_suggestion = true;
            }
        }
    }

    // 3. Single character substitutions
    for (int i = 0; i < word_len; i++) {
        char original_char = misspelled_word[i];
        for (char c = 'a'; c <= 'z'; c++) {
            strcpy(temp_word, misspelled_word);
            temp_word[i] = c;
            if (checkWord(temp_word)) {
                printf("  - %s\n", temp_word);
                found_suggestion = true;
            }
        }
    }

    if (!found_suggestion) {
        printf("  No suggestions found.\n");
    }
}

// Function to load a dictionary (for demonstration)
void loadDictionary() {
    insertWord("apple");
    insertWord("apply");
    insertWord("banana");
    insertWord("bandana");
    insertWord("cat");
    insertWord("cot");
    insertWord("dog");
    insertWord("dig");
    insertWord("hello");
    insertWord("help");
    insertWord("world");
    insertWord("word");
}

int main() {
    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    loadDictionary();

    printf("--- Spell Checker ---\n");

    char test_word[MAX_WORD_LEN];

    printf("Enter a word to check (or 'quit' to exit): ");
    while (scanf("%s", test_word) == 1 && strcmp(test_word, "quit") != 0) {
        if (checkWord(test_word)) {
            printf("'%s' is spelled correctly.\n", test_word);
        } else {
            printf("'%s' is misspelled.\n", test_word);
            suggestCorrections(test_word);
        }
        printf("\nEnter a word to check (or 'quit' to exit): ");
    }

    // Free memory (simplified for this example)
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node* current = hashTable[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
