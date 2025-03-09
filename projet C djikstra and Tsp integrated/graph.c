#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Graph* createGraph(int numVertices, int numEdges) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));
    graph->edges = (Edge*)malloc(numEdges * sizeof(Edge));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;

   
    for (int i = 0; i < numVertices; i++) {
        graph->vertices[i].id = i + 1;
    }

    return graph;
}
int isValidVertex(Graph* graph, int vertex) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].id == vertex) {
            return 1; 
        }
    }
    return 0; 
}


void addEdge(Graph* graph, int src, int dest, int weight, int index) {
    if (index < 0 || index >= graph->numEdges) {
        printf("Invalid edge index!\n");
        return;
    }
    if (!isValidVertex(graph, src)) {
        printf("Source vertex %d does not exist!\n", src);
        return;
    }
    if (!isValidVertex(graph, dest)) {
        printf("Destination vertex %d does not exist!\n", dest);
        return;
    }
    graph->edges[index].src = src;
    graph->edges[index].dest = dest;
    graph->edges[index].weight = weight;
}

void displayGraph(Graph* graph) {
    printf("Vertices:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("City %d\n", graph->vertices[i].id);
    }

    printf("\nEdges:\n");
    for (int i = 0; i < graph->numEdges; i++) {
        printf("City %d -> City %d (Weight: %d)\n",
               graph->edges[i].src,
               graph->edges[i].dest,
               graph->edges[i].weight);
    }
}

void freeGraph(Graph* graph) {
    if (graph) {
        free(graph->vertices);
        free(graph->edges);
        free(graph);
    }
}
int** createDistanceMatrix(Graph* graph) {
    int n = graph->numVertices;
    int** distanceMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        distanceMatrix[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                distanceMatrix[i][j] = 0; // Distance to itself is 0
            } else {
                distanceMatrix[i][j] = dijkstra(graph, i + 1, j + 1); // 1-based indexing
            }
        }
    }

    return distanceMatrix;
}
void freeDistanceMatrix(int** distanceMatrix, int n) {
    for (int i = 0; i < n; i++) {
        free(distanceMatrix[i]);
    }
    free(distanceMatrix);
}

int dijkstra(Graph* graph, int src, int dest) {
    int* distances = (int*)malloc(graph->numVertices * sizeof(int));
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));

    if (!distances || !visited) {
        printf("Memory allocation failed!\n");
        return -1;
    }

   
    for (int i = 0; i < graph->numVertices; i++) {
        distances[i] = INT_MAX;
    }
    distances[src - 1] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++) {
        int u = -1, minDist = INT_MAX;

        
        for (int j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && distances[j] < minDist) {
                minDist = distances[j];
                u = j;
            }
        }

        if (u == -1) break; 
        visited[u] = 1;

        
        for (int j = 0; j < graph->numEdges; j++) {
            Edge edge = graph->edges[j];
            if (edge.src - 1 == u) { 
                int v = edge.dest - 1; 
                if (!visited[v] && distances[u] != INT_MAX &&
                    distances[u] + edge.weight < distances[v]) {
                    distances[v] = distances[u] + edge.weight;
                }
            }
        }
    }

    int result = distances[dest - 1];
    if (result == INT_MAX) {
        printf("No path from City %d to City %d.\n", src, dest);
        result = -1;
    }

    free(distances);
    free(visited);
    return result;
}
