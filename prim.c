#include <stdio.h>
#include <limits.h>

#define MAX 20

int n;
int dist[MAX][MAX];   // Distances
int key[MAX];         // Cheapest
int parent[MAX];      // Tree
int inMST[MAX];       // Included

// Minimum
int minKey() {
    int min = INT_MAX, idx = -1;
    for (int v = 0; v < n; v++)
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            idx = v;
        }
    return idx;
}

int main() {
    // Input
    printf("Enter number of neighbourhoods: ");
    scanf("%d", &n);
    printf("Enter %dx%d distance matrix (0 = no road):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);

    // Initialize
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        inMST[i] = 0;
        parent[i] = -1;
    }
    key[0] = 0;   // Start

    // Prim
    for (int count = 0; count < n; count++) {
        int u = minKey();   // Pick
        if (u == -1) {
            printf("Not all neighbourhoods can be connected!\n");
            return 0;
        }
        inMST[u] = 1;

        // Update
        for (int v = 0; v < n; v++)
            if (dist[u][v] != 0 && !inMST[v] && dist[u][v] < key[v]) {
                key[v] = dist[u][v];
                parent[v] = u;
            }
    }

    // Result
    int total = 0;
    printf("\nRoads selected:\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d : %d\n", parent[i], i, dist[parent[i]][i]);
        total += dist[parent[i]][i];
    }
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
