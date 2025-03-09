#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include<stdlib.h>

int main() {
    int n = 4; 
    int numEdges = 12; 
    Graph* graph = createGraph(n, numEdges);

    addEdge(graph, 1, 2, 10, 0);
    addEdge(graph, 1, 3, 15, 1);
    addEdge(graph, 1, 4, 20, 2);
    addEdge(graph, 2, 1, 10, 3);
    addEdge(graph, 2, 3, 35, 4);
    addEdge(graph, 2, 4, 25, 5);
    addEdge(graph, 3, 1, 15, 6);
    addEdge(graph, 3, 2, 35, 7);
    addEdge(graph, 3, 4, 30, 8);
    addEdge(graph, 4, 1, 20, 9);
    addEdge(graph, 4, 2, 25, 10);
    addEdge(graph, 4, 3, 30, 11);

    displayGraph(graph);


    int path[n], fpath[n], sc[n];
    long long fsum = LLONG_MAX, sum = 0;

    
    for (int i = 0; i < n; i++) {
        path[i] = i;
        sc[i] = i + 1; 
    }

    
    TSP(graph, path, fpath, &sum, &fsum, 0, n, n - 1, 0, sc);

    
    printf("\nOptimal Route:\n");
    for (int i = 0; i < n; i++) {
        printf("City %d -> ", fpath[i]);
    }
    printf("City %d\n", fpath[0]); 

    printf("Minimum Cost: %lld\n", fsum);

   
   
  
    int src, dest;
    printf("\nEnter source city: ");
    scanf("%d", &src);
    printf("Enter destination city: ");
    scanf("%d", &dest);

    if (src < 1 || src > graph->numVertices ) {
      printf("Invalid source  city.\n");}
    if ( dest < 1 || dest > graph->numVertices) {
      printf("Invalid  destination city.\n");}
    else {
      int shortestDistance = dijkstra(graph, src, dest);
      if (shortestDistance == -1) {
          printf("No path exists between City %d and City %d.\n", src, dest);
       } else {
          printf("Shortest path from City %d to City %d: %d\n", src, dest, shortestDistance);
         }
    }
    freeGraph(graph);
    return 0;
 
}
    
