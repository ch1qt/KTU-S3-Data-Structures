#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure for a graph node
struct Node {
    int data;
    struct Node* next;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// Structure for Queue (for BFS)
struct Queue {
    int items[MAX_NODES];
    int front;
    int rear;
};

// Structure for Stack (for DFS iterative)
struct Stack {
    int items[MAX_NODES];
    int top;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src for undirected graph
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Queue functions for BFS
struct Queue* createQueue() {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX_NODES - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// BFS function
void bfs(struct Graph* graph, int startVertex) {
    struct Queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    printf("BFS Traversal: ");

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->data;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(q);
}

// Stack functions for DFS (iterative)
struct Stack* createStack() {
    struct Stack* s = malloc(sizeof(struct Stack));
    s->top = -1;
    return s;
}

void push(struct Stack* s, int value) {
    if (s->top == MAX_NODES - 1)
        printf("\nStack is Full!!");
    else {
        s->top++;
        s->items[s->top] = value;
    }
}

int pop(struct Stack* s) {
    int item;
    if (s->top == -1) {
        printf("Stack is empty");
        item = -1;
    } else {
        item = s->items[s->top];
        s->top--;
    }
    return item;
}

int isStackEmpty(struct Stack* s) {
    return s->top == -1;
}

// DFS function (recursive)
void dfsRecursive(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0) {
            dfsRecursive(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// DFS function (iterative)
void dfsIterative(struct Graph* graph, int startVertex) {
    struct Stack* s = createStack();

    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0; // Reset visited array for DFS
    }

    push(s, startVertex);
    graph->visited[startVertex] = 1; // Mark as visited when pushed

    printf("DFS Traversal (Iterative): ");

    while (!isStackEmpty(s)) {
        int currentVertex = pop(s);
        printf("%d ", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                push(s, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(s);
}


int main() {
    int numVertices = 5;
    struct Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);

    printf("Graph Traversal using BFS and DFS\n");

    // BFS
    for (int i = 0; i < numVertices; i++) {
        graph->visited[i] = 0; // Reset visited array for BFS
    }
    bfs(graph, 0);

    // DFS (Recursive)
    for (int i = 0; i < numVertices; i++) {
        graph->visited[i] = 0; // Reset visited array for DFS
    }
    printf("DFS Traversal (Recursive): ");
    dfsRecursive(graph, 0);
    printf("\n");

    // DFS (Iterative)
    dfsIterative(graph, 0);


    // Free memory
    for (int i = 0; i < numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        while (temp) {
            struct Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);

    return 0;
}
