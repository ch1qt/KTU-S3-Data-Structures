#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 5 // Maximum size of the queue

int queue[MAX_SIZE];
int front = -1;
int rear = -1;
int count = 0; // To keep track of the number of elements

// Function to check if the queue is empty
bool isEmpty() {
    return count == 0;
}

// Function to check if the queue is full
bool isFull() {
    return count == MAX_SIZE;
}

// Function to add an element to the queue (Enqueue)
void enqueue(int data) {
    if (isFull()) {
        printf("Queue Overflow! Cannot enqueue %d\n", data);
        return;
    }
    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % MAX_SIZE; // Circular increment for rear
    queue[rear] = data;
    count++;
    printf("%d enqueued to queue.\n", data);
}

// Function to remove an element from the queue (Dequeue)
int dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1; // Return a sentinel value for error
    }
    int data = queue[front];
    front = (front + 1) % MAX_SIZE; // Circular increment for front
    count--;
    if (isEmpty()) { // Reset front and rear if queue becomes empty
        front = -1;
        rear = -1;
    }
    printf("%d dequeued from queue.\n", data);
    return data;
}

// Function to get the front element of the queue without removing it (Peek)
int peek() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return -1; // Return a sentinel value for error
    }
    return queue[front];
}

// Function to display the elements of the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    int i;
    for (i = 0; i < count; i++) {
        printf("%d ", queue[(front + i) % MAX_SIZE]);
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
