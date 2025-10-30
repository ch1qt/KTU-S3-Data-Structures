#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define R 5 // Number of rows
#define C 5 // Number of columns

// Structure to represent a cell in the maze
struct Cell {
    int row;
    int col;
};

// Queue for BFS
struct Cell queue[R * C];
int front = -1, rear = -1;

void enqueue(struct Cell c) {
    if (rear == R * C - 1) {
        // Queue is full, should not happen in this problem if maze size is reasonable
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = c;
}

struct Cell dequeue() {
    struct Cell c = {-1, -1};
    if (front == -1 || front > rear) {
        // Queue is empty
        return c;
    }
    c = queue[front];
    front++;
    return c;
}

int isEmptyQueue() {
    return front == -1 || front > rear;
}

// Directions for moving (up, down, left, right)
int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

// Function to check if a cell is valid (within bounds and not an obstacle)
int isValid(int row, int col, int maze[R][C]) {
    return (row >= 0 && row < R && col >= 0 && col < C && maze[row][col] != -1);
}

void findShortestDistances(int maze[R][C], int distances[R][C]) {
    int i, j;

    // Initialize distances with INT_MAX and enqueue all landmines
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (maze[i][j] == 1) { // Landmine
                distances[i][j] = 0;
                enqueue((struct Cell){i, j});
            } else if (maze[i][j] == -1) { // Obstacle
                distances[i][j] = -1; // Mark obstacles with -1 distance
            } else {
                distances[i][j] = INT_MAX; // Unvisited non-landmine cell
            }
        }
    }

    // BFS
    while (!isEmptyQueue()) {
        struct Cell current = dequeue();

        for (i = 0; i < 4; i++) { // Explore 4 directions
            int newRow = current.row + dRow[i];
            int newCol = current.col + dCol[i];

            if (isValid(newRow, newCol, maze) && distances[newRow][newCol] == INT_MAX) {
                distances[newRow][newCol] = distances[current.row][current.col] + 1;
                enqueue((struct Cell){newRow, newCol});
            }
        }
    }
}

void printDistances(int distances[R][C]) {
    int i, j;
    printf("Shortest Distances from Landmines:\n");
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (distances[i][j] == INT_MAX) {
                printf("INF "); // Unreachable
            } else if (distances[i][j] == -1) {
                printf("OBS "); // Obstacle
            } else {
                printf("%3d ", distances[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    // Example Maze: 0 = empty, 1 = landmine, -1 = obstacle
    int maze[R][C] = {
        {0, 0, 0, 0, 0},
        {0, -1, 0, -1, 0},
        {0, 0, 1, 0, 0},
        {0, -1, 0, -1, 0},
        {0, 0, 0, 0, 0}
    };

    int distances[R][C];

    findShortestDistances(maze, distances);
    printDistances(distances);

    return 0;
}
