#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the graph
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent a queue for BFS
struct Queue {
    int front, rear;
    int capacity; // Capacity of the queue
    int* array;   // Array to store queue elements
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a queue
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = -1; // Initialize front and rear
    queue->capacity = capacity;      // Set queue capacity
    queue->array = (int*)malloc(capacity * sizeof(int)); // Allocate memory for queue elements
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Function to enqueue an element
void enqueue(struct Queue* queue, int item) {
    if (queue->rear == queue->capacity - 1) { // Check if queue is full
        printf("Queue is full!\n");
        return;
    }
    if (queue->front == -1) // If queue was empty, set front to 0
        queue->front = 0;
    queue->rear++; // Increment rear
    queue->array[queue->rear] = item; // Add item to rear of the queue
}

// Function to dequeue an element
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) { // Check if queue is empty
        printf("Queue is empty!\n");
        return -1;
    }
    int item = queue->array[queue->front]; // Get item from front
    queue->front++; // Increment front
    if (queue->front > queue->rear) // If front crosses rear, reset queue
        queue->front = queue->rear = -1;
    return item;
}

// Function to perform Breadth First Search
void BFS(int** graph, int vertices, int startVertex) {
    struct Queue* queue = createQueue(vertices); // Create a queue with capacity equal to number of vertices
    int visited[vertices]; // Array to keep track of visited vertices
    for (int i = 0; i < vertices; i++)
        visited[i] = 0; // Initialize all vertices as not visited
    visited[startVertex] = 1; // Mark the start vertex as visited
    enqueue(queue, startVertex); // Enqueue the start vertex

    while (!isEmpty(queue)) { // Continue until the queue is empty
        int currentVertex = dequeue(queue); // Dequeue a vertex
        printf("%d ", currentVertex); // Print the vertex

        for (int i = 0; i < vertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) { // Visit adjacent vertices
                visited[i] = 1; // Mark as visited
                enqueue(queue, i); // Enqueue the adjacent vertex
            }
        }
    }
}

int main() {
    int vertices = 6; // Number of vertices in the graph

    // Allocate memory for the adjacency matrix
    int** graph = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
            graph[i][j] = 0; // Initialize all edges as unconnected
    }

    // Adding edges to the graph
    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][3] = 1;
    graph[1][4] = 1;
    graph[2][4] = 1;
    graph[3][5] = 1;
    graph[4][5] = 1;

    printf("Breadth First Traversal starting from vertex 0:\n");
    BFS(graph, vertices, 0); // Perform BFS starting from vertex 0

    // Free allocated memory
    for (int i = 0; i < vertices; i++)
        free(graph[i]);
    free(graph);

    return 0;
}

/*
Graph :

   0
  / \
 1   2
 |   |
 3---4
 |
 5

 
Output of BFS starting from vertex 0:
0 1 2 3 4 5



*/