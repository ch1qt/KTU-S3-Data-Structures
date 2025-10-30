#include <stdio.h>
#include <stdlib.h>

// Structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Structure for a min-heap node
struct MinHeapNode {
    int data;
    struct Node* list_ptr; // Pointer to the list from which element is taken
};

// Min-Heap structure
struct MinHeap {
    int size;
    struct MinHeapNode* heap;
};

// Function to create a new linked list node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Function to swap two min-heap nodes
void swap(struct MinHeapNode* a, struct MinHeapNode* b) {
    struct MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify-down function for min-heap
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->heap[left].data < minHeap->heap[smallest].data) {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->heap[right].data < minHeap->heap[smallest].data) {
        smallest = right;
    }

    if (smallest != idx) {
        swap(&minHeap->heap[smallest], &minHeap->heap[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to build a min-heap
struct MinHeap* buildMinHeap(struct Node* lists[], int k) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = k;
    minHeap->heap = (struct MinHeapNode*)malloc(k * sizeof(struct MinHeapNode));

    for (int i = 0; i < k; i++) {
        minHeap->heap[i].data = lists[i]->data;
        minHeap->heap[i].list_ptr = lists[i];
    }

    for (int i = (k - 1) / 2; i >= 0; i--) {
        minHeapify(minHeap, i);
    }
    return minHeap;
}

// Function to merge k sorted lists
struct Node* mergeKSortedLists(struct Node* lists[], int k) {
    struct MinHeap* minHeap = buildMinHeap(lists, k);
    struct Node* resultHead = NULL;
    struct Node* resultTail = NULL;

    while (minHeap->size > 0) {
        struct MinHeapNode root = minHeap->heap[0];
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = root.data;
        newNode->next = NULL;

        if (resultHead == NULL) {
            resultHead = resultTail = newNode;
        } else {
            resultTail->next = newNode;
            resultTail = newNode;
        }

        if (root.list_ptr->next != NULL) {
            minHeap->heap[0].data = root.list_ptr->next->data;
            minHeap->heap[0].list_ptr = root.list_ptr->next;
        } else {
            minHeap->heap[0] = minHeap->heap[minHeap->size - 1];
            minHeap->size--;
        }
        minHeapify(minHeap, 0);
    }

    free(minHeap->heap);
    free(minHeap);

    return resultHead;
}

// Function to print a linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int k = 3; // Number of sorted lists
    struct Node* lists[k];

    // Create 3 sorted lists
    lists[0] = newNode(1);
    lists[0]->next = newNode(5);
    lists[0]->next->next = newNode(9);

    lists[1] = newNode(2);
    lists[1]->next = newNode(6);
    lists[1]->next->next = newNode(10);

    lists[2] = newNode(3);
    lists[2]->next = newNode(7);
    lists[2]->next->next = newNode(11);

    printf("Original sorted lists:\n");
    for (int i = 0; i < k; i++) {
        printf("List %d: ", i + 1);
        printList(lists[i]);
    }

    struct Node* mergedList = mergeKSortedLists(lists, k);

    printf("\nMerged sorted list:\n");
    printList(mergedList);

    // Free memory (simplified for this example)
    // In a real application, a proper deallocation function would be needed.

    return 0;
}
