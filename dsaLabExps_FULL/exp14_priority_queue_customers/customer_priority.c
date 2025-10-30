#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

// Customer structure
struct Customer {
    int id;
    char category[50];
    int priority_value;
};

// Priority Queue (Max-Heap implementation)
struct Customer priorityQueue[MAX_CUSTOMERS];
int heapSize = 0;

// Function to get priority value based on category
int getPriorityValue(const char* category) {
    if (strcmp(category, "Differently abled") == 0) return 4;
    if (strcmp(category, "Senior citizen") == 0) return 3;
    if (strcmp(category, "Defence personnel") == 0) return 2;
    if (strcmp(category, "Ordinary") == 0) return 1;
    return 0; // Default or error
}

// Heapify-up (for insertion)
void heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && priorityQueue[index].priority_value > priorityQueue[parent].priority_value) {
        // Swap
        struct Customer temp = priorityQueue[index];
        priorityQueue[index] = priorityQueue[parent];
        priorityQueue[parent] = temp;

        index = parent;
        parent = (index - 1) / 2;
    }
}

// Heapify-down (for extraction)
void heapifyDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && priorityQueue[left].priority_value > priorityQueue[largest].priority_value) {
        largest = left;
    }
    if (right < heapSize && priorityQueue[right].priority_value > priorityQueue[largest].priority_value) {
        largest = right;
    }

    if (largest != index) {
        // Swap
        struct Customer temp = priorityQueue[index];
        priorityQueue[index] = priorityQueue[largest];
        priorityQueue[largest] = temp;

        heapifyDown(largest);
    }
}

// Function to add a customer to the priority queue
void addCustomer(int id, const char* category) {
    if (heapSize == MAX_CUSTOMERS) {
        printf("Priority Queue is full. Cannot add more customers.\n");
        return;
    }

    struct Customer newCustomer;
    newCustomer.id = id;
    strcpy(newCustomer.category, category);
    newCustomer.priority_value = getPriorityValue(category);

    priorityQueue[heapSize] = newCustomer;
    heapifyUp(heapSize);
    heapSize++;
    printf("Added Customer ID: %d, Category: %s (Priority: %d)\n", id, category, newCustomer.priority_value);
}

// Function to serve the next customer (extract max priority)
struct Customer serveNextCustomer() {
    struct Customer served = {-1, "", 0}; // Default invalid customer

    if (heapSize == 0) {
        printf("No customers to serve.\n");
        return served;
    }

    served = priorityQueue[0];
    priorityQueue[0] = priorityQueue[heapSize - 1];
    heapSize--;
    heapifyDown(0);

    return served;
}

int main() {
    printf("Adding customers to the priority queue:\n");
    addCustomer(101, "Ordinary");
    addCustomer(102, "Senior citizen");
    addCustomer(103, "Defence personnel");
    addCustomer(104, "Differently abled");
    addCustomer(105, "Ordinary");
    addCustomer(106, "Senior citizen");
    addCustomer(107, "Differently abled");

    printf("\nServing customers in order of priority:\n");
    while (heapSize > 0) {
        struct Customer served = serveNextCustomer();
        if (served.id != -1) {
            printf("Serving Customer ID: %d, Category: %s (Priority: %d)\n", served.id, served.category, served.priority_value);
        }
    }

    serveNextCustomer(); // Try to serve when empty

    return 0;
}
