#include<stdlib.h>
#include<stdio.h>

typedef struct Vertex {
    int id;  
} Vertex;

typedef struct Edge {
    int src;    
    int dest;   
    int weight; 
} Edge;

typedef struct Graph {
    Vertex* vertices;  
    Edge* edges;       
    int numVertices;   
    int numEdges;      
} Graph;


Graph* createGraph(int numVertices, int numEdges);
void addEdge(Graph* graph, int src, int dest, int weight, int index);
void displayGraph(Graph* graph);
int dijkstra(Graph* graph, int src, int dest);
int getEdgeCost(Graph* graph, int src, int dest) ;
void TSP(Graph* graph, int* path, int* fpath, long long* sum, long long* fsum, int flag, int n, int b, int a, int* sc);

void freeGraph(Graph* graph);

