#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];

// Find
int findSet(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findSet(parent[x]);   // Compress
}

// Union
int unite(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a == b) return 0;   // Cycle
    parent[a] = b;
    return 1;
}

// Compare
int cmpEdge(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int main() {
    int n, m = 0;
    int dist[MAX][MAX];
    Edge edges[MAX * MAX];

    // Input
    printf("Enter number of neighbourhoods: ");
    scanf("%d", &n);
    printf("Enter %dx%d distance matrix (0 = no road):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);

    // Edges
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (dist[i][j] != 0) {
                edges[m].u = i;
                edges[m].v = j;
                edges[m].w = dist[i][j];
                m++;
            }

    // Sort
    qsort(edges, m, sizeof(Edge), cmpEdge);

    // Parent
    for (int i = 0; i < n; i++) parent[i] = i;

    int total = 0, count = 0;
    printf("\nRoads selected:\n");

    // Kruskal
    for (int i = 0; i < m; i++) {
        if (unite(edges[i].u, edges[i].v)) {   // Accept
            printf("%d - %d : %d\n", edges[i].u, edges[i].v, edges[i].w);
            total += edges[i].w;
            count++;
        }
    }

    // Result
    if (count < n - 1)
        printf("Not all neighbourhoods can be connected!\n");
    else
        printf("Total length: %d\n", total);

    return 0;
}

/*
Sample input:
5
0 2 3 6 0
2 0 4 5 7
3 4 0 0 8
6 5 0 0 9
0 7 8 9 0

Output total: 17
*/
