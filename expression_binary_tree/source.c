#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure for a node in the expression tree
struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Stack for TreeNode pointers (used for building the tree)
struct NodeStack {
    struct TreeNode* items[MAX_SIZE];
    int top;
};

void initNodeStack(struct NodeStack* s) {
    s->top = -1;
}

int isNodeStackEmpty(struct NodeStack* s) {
    return s->top == -1;
}

void pushNode(struct NodeStack* s, struct TreeNode* node) {
    if (s->top == MAX_SIZE - 1) {
        printf("Node Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = node;
}

struct TreeNode* popNode(struct NodeStack* s) {
    if (isNodeStackEmpty(s)) {
        printf("Node Stack Underflow\n");
        return NULL;
    }
    return s->items[(s->top)--];
}

// Stack for characters (used for infix to postfix conversion)
struct CharStack {
    char items[MAX_SIZE];
    int top;
};

void initCharStack(struct CharStack* s) {
    s->top = -1;
}

int isCharStackEmpty(struct CharStack* s) {
    return s->top == -1;
}

void pushChar(struct CharStack* s, char value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Char Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

char popChar(struct CharStack* s) {
    if (isCharStackEmpty(s)) {
        printf("Char Stack Underflow\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

char peekChar(struct CharStack* s) {
    if (isCharStackEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to get precedence of an operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Function to convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    struct CharStack s;
    initCharStack(&s);
    int i = 0, j = 0;
    char nextChar;

    while ((nextChar = infix[i++]) != '\0') {
        if (isalnum(nextChar)) {
            postfix[j++] = nextChar;
        } else if (nextChar == '(') {
            pushChar(&s, nextChar);
        } else if (nextChar == ')') {
            while (!isCharStackEmpty(&s) && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
            }
            if (!isCharStackEmpty(&s) && peekChar(&s) == '(') {
                popChar(&s);
            }
        } else if (isOperator(nextChar)) {
            while (!isCharStackEmpty(&s) && peekChar(&s) != '(' && precedence(nextChar) <= precedence(peekChar(&s))) {
                postfix[j++] = popChar(&s);
            }
            pushChar(&s, nextChar);
        }
    }

    while (!isCharStackEmpty(&s)) {
        postfix[j++] = popChar(&s);
    }
    postfix[j] = '\0';
}

// Function to create a new tree node
struct TreeNode* createTreeNode(char data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to build expression tree from postfix expression
struct TreeNode* buildExpressionTree(char postfix[]) {
    struct NodeStack s;
    initNodeStack(&s);
    int i = 0;
    char nextChar;

    while ((nextChar = postfix[i++]) != '\0') {
        struct TreeNode* newNode = createTreeNode(nextChar);
        if (isalnum(nextChar)) { // If operand
            pushNode(&s, newNode);
        } else if (isOperator(nextChar)) { // If operator
            newNode->right = popNode(&s);
            newNode->left = popNode(&s);
            pushNode(&s, newNode);
        }
    }
    return popNode(&s); // The root of the expression tree
}

// Inorder traversal (Infix form)
void inorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;

    // Add parentheses for operators to maintain correct order
    if (isOperator(node->data)) {
        printf("(");
    }
    inorderTraversal(node->left);
    printf("%c", node->data);
    inorderTraversal(node->right);
    if (isOperator(node->data)) {
        printf(")");
    }
}

// Preorder traversal (Prefix form)
void preorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;
    printf("%c", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

// Postorder traversal (Postfix form)
void postorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%c", node->data);
}

// Function to free the memory allocated for the tree
void freeTree(struct TreeNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    struct TreeNode* root = NULL;

    printf("Enter an infix expression (e.g., a+b*c): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    root = buildExpressionTree(postfix);

    printf("\nInfix form: ");
    inorderTraversal(root);
    printf("\n");

    printf("Prefix form: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postfix form: ");
    postorderTraversal(root);
    printf("\n");

    freeTree(root);

    return 0;
}
