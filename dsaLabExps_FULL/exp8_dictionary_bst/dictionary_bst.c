#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50
#define MAX_MEANING_LEN 200

// Structure for a BST node (word-meaning pair)
struct Node {
    char word[MAX_WORD_LEN];
    char meaning[MAX_MEANING_LEN];
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(const char* word, const char* meaning) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a word-meaning pair into the BST
struct Node* insert(struct Node* root, const char* word, const char* meaning) {
    if (root == NULL) {
        return createNode(word, meaning);
    }

    int cmp = strcmp(word, root->word);

    if (cmp < 0) {
        root->left = insert(root->left, word, meaning);
    } else if (cmp > 0) {
        root->right = insert(root->right, word, meaning);
    } else {
        // Word already exists, update meaning
        strcpy(root->meaning, meaning);
    }
    return root;
}

// Function to search for a word and return its meaning
const char* search(struct Node* root, const char* word) {
    if (root == NULL) {
        return "Word not found.";
    }

    int cmp = strcmp(word, root->word);

    if (cmp == 0) {
        return root->meaning;
    } else if (cmp < 0) {
        return search(root->left, word);
    } else {
        return search(root->right, word);
    }
}

// Function for inorder traversal (prints words in alphabetical order)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s: %s\n", root->word, root->meaning);
        inorderTraversal(root->right);
    }
}

// Function to free the memory allocated for the BST
void freeBST(struct Node* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;

    root = insert(root, "apple", "A common, edible fruit.");
    root = insert(root, "banana", "A long, curved fruit.");
    root = insert(root, "cat", "A small domesticated carnivorous mammal.");
    root = insert(root, "dog", "A domesticated carnivorous mammal that typically has a long snout.");
    root = insert(root, "apple", "A round fruit with red or green skin."); // Update meaning

    printf("Dictionary contents (alphabetical order):\n");
    inorderTraversal(root);
    printf("\n");

    printf("Search 'cat': %s\n", search(root, "cat"));
    printf("Search 'apple': %s\n", search(root, "apple"));
    printf("Search 'zebra': %s\n", search(root, "zebra"));

    freeBST(root);

    return 0;
}
