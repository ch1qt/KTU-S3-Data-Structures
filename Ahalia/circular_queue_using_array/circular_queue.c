#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 5 // Maximum size of the circular queue

int cQueue[MAX_SIZE];
int front = -1;
int rear = -1;

// Function to check if the circular queue is empty
bool isEmpty() {
    return front == -1;
}

// Function to check if the circular queue is full
bool isFull() {
    return (rear + 1) % MAX_SIZE == front;
}

// Function to add an element to the circular queue (Enqueue)
void enqueue(int data) {
    if (isFull()) {
        printf("Circular Queue Overflow! Cannot enqueue %d\n", data);
        return;
    }
    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % MAX_SIZE;
    cQueue[rear] = data;
    printf("%d enqueued to circular queue.\n", data);
}

// Function to remove an element from the circular queue (Dequeue)
int dequeue() {
    if (isEmpty()) {
        printf("Circular Queue Underflow! Cannot dequeue.\n");
        return -1; // Return a sentinel value for error
    }
    int data = cQueue[front];
    if (front == rear) { // Only one element was present
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX_SIZE;
    }
    printf("%d dequeued from circular queue.\n", data);
    return data;
}

// Function to get the front element of the circular queue without removing it (Peek)
int peek() {
    if (isEmpty()) {
        printf("Circular Queue is empty!\n");
        return -1; // Return a sentinel value for error
    }
    return cQueue[front];
}

// Function to display the elements of the circular queue
void display() {
    if (isEmpty()) {
        printf("Circular Queue is empty.\n");
        return;
    }
    printf("Circular Queue elements: ");
    int i = front;
    while (true) {
        printf("%d ", cQueue[i]);
        if (i == rear) {
            break;
        }
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    display();

    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    printf("Front element is: %d\n", peek());

    enqueue(40);
    enqueue(50);
    enqueue(60); // This should cause an overflow
    display();

    dequeue();
    dequeue();
    display();

    enqueue(70);
    display();

    dequeue();
    dequeue();
    dequeue();
    dequeue(); // This should cause an underflow
    display();

    return 0;
}
