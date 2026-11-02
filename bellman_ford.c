#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

int u[MAX], v[MAX], w[MAX];   // Edges
int dist[MAX];                // Distances

int main() {
    int V, E, src;

    // Input
    printf("Enter vertices and edges: ");
    scanf("%d %d", &V, &E);
    printf("Enter each edge as: from to weight\n");
    for (int i = 0; i < E; i++)
        scanf("%d %d %d", &u[i], &v[i], &w[i]);
    printf("Enter source: ");
    scanf("%d", &src);

    // Initialize
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    // Relax
    for (int i = 1; i <= V - 1; i++) {
        int changed = 0;
        for (int j = 0; j < E; j++) {
            if (dist[u[j]] != INF && dist[u[j]] + w[j] < dist[v[j]]) {
                dist[v[j]] = dist[u[j]] + w[j];   // Update
                changed = 1;
            }
        }
        if (!changed) break;   // Early
    }

    // Detect
    for (int j = 0; j < E; j++) {
        if (dist[u[j]] != INF && dist[u[j]] + w[j] < dist[v[j]]) {
            printf("Negative cycle detected!\n");
            return 0;
        }
    }

    // Result
    printf("\nShortest distances from %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) printf("%d : unreachable\n", i);
        else printf("%d : %d\n", i, dist[i]);
    }
    return 0;
}

/*
Sample input:
5 8
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3
0

Output: 0:0  1:-1  2:2  3:-2  4:1
*/
