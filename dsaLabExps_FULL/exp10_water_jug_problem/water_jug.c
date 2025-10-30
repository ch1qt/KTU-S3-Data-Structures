#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Container capacities
#define CAP1 10 // 10-litre container
#define CAP2 7  // 7-litre container
#define CAP3 4  // 4-litre container

// Structure to represent a state (water levels in the three jugs)
struct State {
    int jug10;
    int jug7;
    int jug4;
};

// Queue for BFS
struct State queue[CAP1 * CAP2 * CAP3]; // Max possible states
int front = -1, rear = -1;

void enqueue(struct State s) {
    if (rear == (CAP1 * CAP2 * CAP3) - 1) {
        // Queue full, should not happen with appropriate size
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = s;
}

struct State dequeue() {
    struct State s = {-1, -1, -1};
    if (front == -1 || front > rear) {
        // Queue empty
        return s;
    }
    s = queue[front];
    front++;
    return s;
}

bool isEmptyQueue() {
    return front == -1 || front > rear;
}

// Visited array to keep track of states
bool visited[CAP1 + 1][CAP2 + 1][CAP3 + 1];

// Function to check if a state is the goal state
bool isGoalState(struct State s) {
    return (s.jug7 == 2 || s.jug4 == 2);
}

// Function to perform pouring operation
// from_cap, to_cap: capacities of source and destination jugs
// from_current, to_current: current water levels in source and destination jugs
void pour(int from_cap, int to_cap, int from_current, int to_current, int *new_from, int *new_to) {
    int amount_to_pour = (from_current < (to_cap - to_current)) ? from_current : (to_cap - to_current);
    *new_from = from_current - amount_to_pour;
    *new_to = to_current + amount_to_pour;
}

// BFS to find the solution
bool solveWaterJugProblem() {
    // Initialize visited array to false
    for (int i = 0; i <= CAP1; i++) {
        for (int j = 0; j <= CAP2; j++) {
            for (int k = 0; k <= CAP3; k++) {
                visited[i][j][k] = false;
            }
        }
    }

    // Initial state: (0, 7, 4)
    struct State initialState = {0, CAP2, CAP3};
    enqueue(initialState);
    visited[initialState.jug10][initialState.jug7][initialState.jug4] = true;

    while (!isEmptyQueue()) {
        struct State current = dequeue();

        if (isGoalState(current)) {
            printf("Goal state reached: (10L: %d, 7L: %d, 4L: %d)\n", current.jug10, current.jug7, current.jug4);
            return true;
        }

        // Generate next states by pouring
        struct State next;
        int new_from, new_to;

        // Pour from 10L to 7L
        pour(CAP1, CAP2, current.jug10, current.jug7, &new_from, &new_to);
        next = (struct State){new_from, new_to, current.jug4};
        if (!visited[next.jug10][next.jug7][next.jug4]) {
            visited[next.jug10][next.jug7][next.jug4] = true;
            enqueue(next);
        }

        // Pour from 10L to 4L
        pour(CAP1, CAP3, current.jug10, current.jug4, &new_from, &new_to);
        next = (struct State){new_from, current.jug7, new_to};
        if (!visited[next.jug10][next.jug7][next.jug4]) {
            visited[next.jug10][next.jug7][next.jug4] = true;
            enqueue(next);
        }

        // Pour from 7L to 10L
        pour(CAP2, CAP1, current.jug7, current.jug10, &new_from, &new_to);
        next = (struct State){new_to, new_from, current.jug4};
        if (!visited[next.jug10][next.jug7][next.jug4]) {
            visited[next.jug10][next.jug7][next.jug4] = true;
            enqueue(next);
        }

        // Pour from 7L to 4L
        pour(CAP2, CAP3, current.jug7, current.jug4, &new_from, &new_to);
        next = (struct State){current.jug10, new_from, new_to};
        if (!visited[next.jug10][next.jug7][next.jug4]) {
            visited[next.jug10][next.jug7][next.jug4] = true;
            enqueue(next);
        }

        // Pour from 4L to 10L
        pour(CAP3, CAP1, current.jug4, current.jug10, &new_from, &new_to);
        next = (struct State){new_to, current.jug7, new_from};
        if (!visited[next.jug10][next.jug7][next.jug4]) {
            visited[next.jug10][next.jug7][next.jug4] = true;
            enqueue(next);
        }

        // Pour from 4L to 7L
        pour(CAP3, CAP2, current.jug4, current.jug7, &new_from, &new_to);
        next = (struct State){current.jug10, new_to, new_from};
        if (!visited[next.jug10][next.jug7][next.jug4]) {
            visited[next.jug10][next.jug7][next.jug4] = true;
            enqueue(next);
        }
    }

    return false; // Goal not reachable
}

int main() {
    if (solveWaterJugProblem()) {
        printf("\nIt is possible to get exactly 2 litres in the 7L or 4L container.\n");
    } else {
        printf("\nIt is NOT possible to get exactly 2 litres in the 7L or 4L container.\n");
    }

    return 0;
}
