#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Simple Queue
int queue[MAX_SIZE];
int front = -1, rear = -1;

void enqueue(int item) {
    if (rear == MAX_SIZE - 1) {
        printf("Queue is full\n");
    } else {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = item;
        printf("Enqueued %d\n", item);
    }
}

void dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
    } else {
        printf("Dequeued %d\n", queue[front]);
        front++;
    }
}

// Circular Queue
int cQueue[MAX_SIZE];
int cFront = -1, cRear = -1;

void cEnqueue(int item) {
    if ((cFront == 0 && cRear == MAX_SIZE - 1) || (cRear == (cFront - 1) % (MAX_SIZE - 1))) {
        printf("Circular Queue is full\n");
    } else {
        if (cFront == -1) {
            cFront = cRear = 0;
            cQueue[cRear] = item;
        } else if (cRear == MAX_SIZE - 1 && cFront != 0) {
            cRear = 0;
            cQueue[cRear] = item;
        } else {
            cRear++;
            cQueue[cRear] = item;
        }
        printf("Enqueued %d to Circular Queue\n", item);
    }
}

void cDequeue() {
    if (cFront == -1) {
        printf("Circular Queue is empty\n");
    } else {
        printf("Dequeued %d from Circular Queue\n", cQueue[cFront]);
        if (cFront == cRear) {
            cFront = cRear = -1;
        } else if (cFront == MAX_SIZE - 1) {
            cFront = 0;
        } else {
            cFront++;
        }
    }
}

// Dequeue (Double-Ended Queue)
int deQueue[MAX_SIZE];
int dFront = -1, dRear = -1;

void dEnqueueRear(int item) {
    if ((dFront == 0 && dRear == MAX_SIZE - 1) || (dFront == dRear + 1)) {
        printf("Dequeue is full\n");
    } else {
        if (dFront == -1) {
            dFront = dRear = 0;
        } else if (dRear == MAX_SIZE - 1) {
            dRear = 0;
        } else {
            dRear++;
        }
        deQueue[dRear] = item;
        printf("Enqueued %d at rear of Dequeue\n", item);
    }
}

void dDequeueFront() {
    if (dFront == -1) {
        printf("Dequeue is empty\n");
    } else {
        printf("Dequeued %d from front of Dequeue\n", deQueue[dFront]);
        if (dFront == dRear) {
            dFront = dRear = -1;
        } else if (dFront == MAX_SIZE - 1) {
            dFront = 0;
        } else {
            dFront++;
        }
    }
}

int main() {
    // Simple Queue
    enqueue(10);
    enqueue(20);
    dequeue();
    dequeue();
    dequeue();

    printf("\n");

    // Circular Queue
    cEnqueue(10);
    cEnqueue(20);
    cEnqueue(30);
    cEnqueue(40);
    cEnqueue(50);
    cDequeue();
    cEnqueue(60);
    cDequeue();

    printf("\n");

    // Dequeue
    dEnqueueRear(10);
    dEnqueueRear(20);
    dDequeueFront();
    dDequeueFront();
    dDequeueFront();

    return 0;
}
