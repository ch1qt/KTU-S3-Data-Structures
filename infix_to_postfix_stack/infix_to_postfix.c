#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure for characters (operators)
struct CharStack {
    char items[MAX_SIZE];
    int top;
};

// Stack structure for integers (operands)
struct IntStack {
    int items[MAX_SIZE];
    int top;
};

// Initialize character stack
void initCharStack(struct CharStack* s) {
    s->top = -1;
}

// Check if character stack is empty
int isCharStackEmpty(struct CharStack* s) {
    return s->top == -1;
}

// Check if character stack is full
int isCharStackFull(struct CharStack* s) {
    return s->top == MAX_SIZE - 1;
}

// Push character onto stack
void pushChar(struct CharStack* s, char value) {
    if (isCharStackFull(s)) {
        printf("Char Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

// Pop character from stack
char popChar(struct CharStack* s) {
    if (isCharStackEmpty(s)) {
        printf("Char Stack Underflow\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

// Peek character from stack
char peekChar(struct CharStack* s) {
    if (isCharStackEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// Initialize integer stack
void initIntStack(struct IntStack* s) {
    s->top = -1;
}

// Check if integer stack is empty
int isIntStackEmpty(struct IntStack* s) {
    return s->top == -1;
}

// Check if integer stack is full
int isIntStackFull(struct IntStack* s) {
    return s->top == MAX_SIZE - 1;
}

// Push integer onto stack
void pushInt(struct IntStack* s, int value) {
    if (isIntStackFull(s)) {
        printf("Int Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

// Pop integer from stack
int popInt(struct IntStack* s) {
    if (isIntStackEmpty(s)) {
        printf("Int Stack Underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
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
        if (isalnum(nextChar)) { // If operand, append to postfix
            postfix[j++] = nextChar;
        } else if (nextChar == '(') { // If '(', push to stack
            pushChar(&s, nextChar);
        } else if (nextChar == ')') { // If ')', pop and append until '(' is found
            while (!isCharStackEmpty(&s) && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
            }
            if (!isCharStackEmpty(&s) && peekChar(&s) == '(') {
                popChar(&s); // Pop '('
            }
        } else { // If operator
            while (!isCharStackEmpty(&s) && precedence(nextChar) <= precedence(peekChar(&s))) {
                postfix[j++] = popChar(&s);
            }
            pushChar(&s, nextChar);
        }
    }

    // Pop any remaining operators from the stack
    while (!isCharStackEmpty(&s)) {
        postfix[j++] = popChar(&s);
    }
    postfix[j] = '\0'; // Null-terminate the postfix string
}

// Function to evaluate a postfix expression
int evaluatePostfix(char postfix[]) {
    struct IntStack s;
    initIntStack(&s);
    int i = 0;
    char nextChar;
    int operand1, operand2;

    while ((nextChar = postfix[i++]) != '\0') {
        if (isdigit(nextChar)) { // If digit, convert to int and push
            pushInt(&s, nextChar - '0');
        } else { // If operator, pop two operands, operate, and push result
            operand2 = popInt(&s);
            operand1 = popInt(&s);

            switch (nextChar) {
                case '+':
                    pushInt(&s, operand1 + operand2);
                    break;
                case '-':
                    pushInt(&s, operand1 - operand2);
                    break;
                case '*':
                    pushInt(&s, operand1 * operand2);
                    break;
                case '/':
                    pushInt(&s, operand1 / operand2);
                    break;
                case '^': // Simple power for single digits
                    {
                        int res = 1;
                        for(int k=0; k<operand2; k++) res *= operand1;
                        pushInt(&s, res);
                    }
                    break;
                default:
                    printf("Invalid operator: %c\n", nextChar);
                    return -1; // Error
            }
        }
    }
    return popInt(&s);
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter an infix expression (e.g., 2+3*4): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // For evaluation, assuming single-digit operands for simplicity
    // For multi-digit numbers, parsing would be more complex.
    printf("Evaluation result: %d\n", evaluatePostfix(postfix));

    return 0;
}
