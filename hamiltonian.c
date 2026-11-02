#include <stdio.h>

#define MAX 20

int n;
int g[MAX][MAX];   // Graph
int path[MAX];     // Tour

// Safe
int isSafe(int v, int pos) {
    if (g[path[pos - 1]][v] == 0) return 0;   // Road
    for (int i = 0; i < pos; i++)
        if (path[i] == v) return 0;           // Visited
    return 1;
}

// Solve
int solve(int pos) {
    if (pos == n)   // Complete
        return g[path[n - 1]][path[0]] == 1;   // Return

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;                 // Place
            if (solve(pos + 1)) return 1;  // Next
            path[pos] = -1;                // Undo
        }
    }
    return 0;
}

int main() {
    // Input
    printf("Enter number of cities: ");
    scanf("%d", &n);
    printf("Enter %dx%d adjacency matrix (1 = road, 0 = no road):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    // Start
    for (int i = 0; i < n; i++) path[i] = -1;
    path[0] = 0;

    // Result
    if (solve(1)) {
        printf("Hamiltonian Circuit: ");
        for (int i = 0; i < n; i++) printf("%d -> ", path[i]);
        printf("%d\n", path[0]);
    } else {
        printf("No Hamiltonian Circuit exists\n");
    }
    return 0;
}

/*
Sample input:
6
0 1 1 0 0 1
1 0 1 1 0 0
1 1 0 1 1 0
0 1 1 0 1 1
0 0 1 1 0 1
1 0 0 1 1 0

Output: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 0
*/
