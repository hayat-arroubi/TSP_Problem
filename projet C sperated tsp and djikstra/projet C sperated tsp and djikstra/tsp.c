#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void TSP(Graph* graph, int* path, int* fpath, long long* sum, long long* fsum, int flag, int n, int b, int a, int* sc) {
    if (flag == n) {
        long long currentSum = 0;

        for (int i = 1; i < n; i++) {
            int src = sc[path[i - 1]];
            int dest = sc[path[i]];
            int edgeCost = getEdgeCost(graph, src, dest);

            if (edgeCost == -1) return; 
            currentSum += edgeCost;
        }

        
        int edgeCost = getEdgeCost(graph, sc[path[n - 1]], sc[path[0]]);
        if (edgeCost == -1) return;

        currentSum += edgeCost;

        
        if (currentSum < *fsum) {
            *fsum = currentSum;
            for (int i = 0; i < n; i++) {
                fpath[i] = sc[path[i]];
            }
        }
        return;
    }

   
    for (int i = a; i <= b; i++) {
        int temp = path[a];
        path[a] = path[i];
        path[i] = temp;

        TSP(graph, path, fpath, sum, fsum, flag + 1, n, b, a + 1, sc);

        temp = path[a];
        path[a] = path[i];
        path[i] = temp;
    }
}

int getEdgeCost(Graph* graph, int src, int dest) {
    for (int i = 0; i < graph->numEdges; i++) {
        if (graph->edges[i].src == src && graph->edges[i].dest == dest) {
            return graph->edges[i].weight;
        }
    }
    return -1; 
}

