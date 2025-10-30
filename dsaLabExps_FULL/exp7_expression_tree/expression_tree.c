#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

// Structure for a tree node
struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Structure for a stack (used for both operator stack and tree node stack)
struct Stack {
    int top;
    void* items[MAX_STACK_SIZE]; // Can store chars or TreeNode pointers
};

// Function to initialize a stack
void initStack(struct Stack* s) {
    s->top = -1;
}

// Function to check if stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Function to push an item onto the stack
void push(struct Stack* s, void* item) {
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->items[++s->top] = item;
}

// Function to pop an item from the stack
void* pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->items[s->top--];
}

// Function to peek at the top item of the stack
void* peek(struct Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->items[s->top];
}

// Function to create a new tree node
struct TreeNode* createNode(char data) {
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

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix
void infixToPostfix(char* infix, char* postfix) {
    struct Stack operatorStack;
    initStack(&operatorStack);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&operatorStack, (void*)(long)ch);
        } else if (ch == ')') {
            while (!isEmpty(&operatorStack) && (char)(long)peek(&operatorStack) != '(') {
                postfix[j++] = (char)(long)pop(&operatorStack);
            }
            if (!isEmpty(&operatorStack) && (char)(long)peek(&operatorStack) == '(') {
                pop(&operatorStack); // Pop '('
            } else {
                printf("Invalid expression: Mismatched parentheses\n");
                exit(1);
            }
        } else if (precedence(ch) > 0) { // Operator
            while (!isEmpty(&operatorStack) && (char)(long)peek(&operatorStack) != '(' &&
                   precedence(ch) <= precedence((char)(long)peek(&operatorStack))) {
                postfix[j++] = (char)(long)pop(&operatorStack);
            }
            push(&operatorStack, (void*)(long)ch);
        }
    }

    while (!isEmpty(&operatorStack)) {
        if ((char)(long)peek(&operatorStack) == '(') {
            printf("Invalid expression: Mismatched parentheses\n");
            exit(1);
        }
        postfix[j++] = (char)(long)pop(&operatorStack);
    }
    postfix[j] = '\0';
}

// Function to build expression tree from postfix expression
struct TreeNode* buildExpressionTree(char* postfix) {
    struct Stack nodeStack;
    initStack(&nodeStack);
    int i;

    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        struct TreeNode* newNode = createNode(ch);

        if (isalnum(ch)) {
            push(&nodeStack, newNode);
        } else { // Operator
            newNode->right = (struct TreeNode*)pop(&nodeStack);
            newNode->left = (struct TreeNode*)pop(&nodeStack);
            push(&nodeStack, newNode);
        }
    }
    return (struct TreeNode*)pop(&nodeStack);
}

// Function for pre-order traversal (Prefix expression)
void preOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%c", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Function for post-order traversal (Postfix expression)
void postOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%c", root->data);
    }
}

int main() {
    char infix[MAX_STACK_SIZE];
    char postfix[MAX_STACK_SIZE];
    struct TreeNode* root;

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    root = buildExpressionTree(postfix);

    printf("Prefix expression: ");
    preOrderTraversal(root);
    printf("\n");

    printf("Postfix expression (from tree): ");
    postOrderTraversal(root);
    printf("\n");

    // Free allocated memory (simplified for this example)
    // In a real application, a proper tree deallocation function would be needed.
    return 0;
}
