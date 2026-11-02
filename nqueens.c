#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int n;
int col[MAX];        // Column
int solutions = 0;   // Count

// Safe
int isSafe(int row, int c) {
    for (int i = 0; i < row; i++) {
        if (col[i] == c) return 0;                       // Column
        if (abs(col[i] - c) == abs(i - row)) return 0;   // Diagonal
    }
    return 1;
}

// Print
void printBoard() {
    printf("Solution %d:\n", solutions);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%s", col[i] == j ? "Q " : ". ");
        printf("\n");
    }
    printf("\n");
}

// Solve
void solve(int row) {
    if (row == n) {   // Complete
        solutions++;
        printBoard();
        return;
    }
    for (int c = 0; c < n; c++) {
        if (isSafe(row, c)) {
            col[row] = c;      // Place
            solve(row + 1);    // Next
            col[row] = -1;     // Undo
        }
    }
}

int main() {
    // Input
    printf("Enter N: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) col[i] = -1;

    // Start
    solve(0);

    // Result
    if (solutions == 0)
        printf("No solution exists\n");
    else
        printf("Total solutions: %d\n", solutions);

    return 0;
}
