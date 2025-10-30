#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_SIZE 100

// Stack implementation
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

void push(struct Stack* stack, char op) {
    stack->array[++stack->top] = op;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to return precedence of operators
int precedence(char ch) {
    switch (ch) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

// Function to convert infix to postfix
int infixToPostfix(char* infix, char* postfix) {
    int i, j;
    struct Stack* stack = createStack(strlen(infix));
    if (!stack) return -1;

    for (i = 0, j = -1; infix[i]; ++i) {
        if (isalnum(infix[i]))
            postfix[++j] = infix[i];
        else if (infix[i] == '(')
            push(stack, infix[i]);
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                postfix[++j] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // Invalid expression
            else
                pop(stack);
        } else { // Operator
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack)))
                postfix[++j] = pop(stack);
            push(stack, infix[i]);
        }
    }

    while (!isEmpty(stack))
        postfix[++j] = pop(stack);

    postfix[++j] = '\0';
    return 0;
}

// Function to evaluate postfix expression
int evaluatePostfix(char* postfix) {
    struct Stack* stack = createStack(strlen(postfix));
    int i;

    if (!stack) return -1;

    for (i = 0; postfix[i]; ++i) {
        if (isdigit(postfix[i]))
            push(stack, postfix[i] - '0');
        else {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (postfix[i]) {
            case '+': push(stack, val2 + val1); break;
            case '-': push(stack, val2 - val1); break;
            case '*': push(stack, val2 * val1); break;
            case '/': push(stack, val2 / val1); break;
            }
        }
    }
    return pop(stack);
}

int main() {
    char infix[MAX_EXPR_SIZE];
    char postfix[MAX_EXPR_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result after evaluation: %d\n", result);

    return 0;
}
