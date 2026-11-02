#include <stdio.h>

#define T 6   // Tasks
#define R 4   // Resources

int conflict[T][T];   // Conflict
int allowed[T][R];    // Allowed
int color[T];         // Assigned

// Safe
int isSafe(int task, int res) {
    if (!allowed[task][res]) return 0;            // Forbidden
    for (int i = 0; i < task; i++)
        if (conflict[task][i] && color[i] == res) // Clash
            return 0;
    return 1;
}

// Solve
int solve(int task) {
    if (task == T) return 1;                      // Done
    for (int r = 0; r < R; r++) {
        if (isSafe(task, r)) {
            color[task] = r;                      // Assign
            if (solve(task + 1)) return 1;        // Next
            color[task] = -1;                     // Undo
        }
    }
    return 0;
}

int main() {
    // Input
    printf("Enter %dx%d conflict matrix (1 = tasks cannot share a resource):\n", T, T);
    for (int i = 0; i < T; i++)
        for (int j = 0; j < T; j++)
            scanf("%d", &conflict[i][j]);

    printf("Enter %dx%d allowed matrix (row = task, col = resource, 1 = allowed):\n", T, R);
    for (int i = 0; i < T; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allowed[i][j]);

    for (int i = 0; i < T; i++) color[i] = -1;

    // Result
    if (solve(0)) {
        printf("\nAssignment found:\n");
        for (int i = 0; i < T; i++)
            printf("Task %d -> Resource %d\n", i, color[i]);
    } else {
        printf("\nNo valid assignment exists\n");
    }
    return 0;
}

/*
Sample conflict matrix:
0 1 1 0 0 0
1 0 1 1 0 0
1 1 0 1 1 0
0 1 1 0 1 1
0 0 1 1 0 1
0 0 0 1 1 0

Sample allowed matrix (all allowed):
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
*/
