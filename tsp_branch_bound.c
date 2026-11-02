#include <stdio.h>
#include <limits.h>

#define MAX 15

int n;
int adj[MAX][MAX];     // Costs
int path[MAX];         // Current
int finalPath[MAX];    // Best
int visited[MAX];      // Seen
int finalRes = INT_MAX;   // Best cost

// Smallest
int firstMin(int i) {
    int min = INT_MAX;
    for (int k = 0; k < n; k++)
        if (i != k && adj[i][k] < min) min = adj[i][k];
    return min;
}

// Second
int secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < n; j++) {
        if (i == j) continue;
        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] < second) {
            second = adj[i][j];
        }
    }
    return second;
}

// Branch
void tspRec(int bound, int weight, int level) {
    if (level == n) {   // Complete
        int res = weight + adj[path[n - 1]][path[0]];   // Return
        if (res < finalRes) {
            for (int i = 0; i < n; i++) finalPath[i] = path[i];
            finalRes = res;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && adj[path[level - 1]][i] != 0) {
            int temp = bound;
            weight += adj[path[level - 1]][i];

            // Bound
            if (level == 1)
                bound -= (firstMin(path[level - 1]) + firstMin(i)) / 2;
            else
                bound -= (secondMin(path[level - 1]) + firstMin(i)) / 2;

            // Prune
            if (bound + weight < finalRes) {
                path[level] = i;
                visited[i] = 1;
                tspRec(bound, weight, level + 1);   // Next
            }

            // Undo
            weight -= adj[path[level - 1]][i];
            bound = temp;
            for (int k = 0; k < n; k++) visited[k] = 0;
            for (int j = 0; j < level; j++) visited[path[j]] = 1;
        }
    }
}

int main() {
    // Input
    printf("Enter number of cities: ");
    scanf("%d", &n);
    printf("Enter %dx%d cost matrix (diagonal 0):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    // Initial
    int bound = 0;
    for (int i = 0; i < n; i++)
        bound += firstMin(i) + secondMin(i);
    bound = (bound % 2 == 1) ? bound / 2 + 1 : bound / 2;   // Round

    // Start
    for (int i = 0; i < n; i++) { path[i] = -1; visited[i] = 0; }
    visited[0] = 1;
    path[0] = 0;

    tspRec(bound, 0, 1);

    // Result
    printf("\nMinimum cost: %d\n", finalRes);
    printf("Path: ");
    for (int i = 0; i < n; i++) printf("%d -> ", finalPath[i]);
    printf("%d\n", finalPath[0]);

    return 0;
}

/*
Sample input:
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

Output: cost 80, path 0 -> 1 -> 3 -> 2 -> 0
*/
