#include <stdio.h>
#include <stdlib.h>

// Allocate
int **alloc(int n) {
    int **m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) m[i] = calloc(n, sizeof(int));
    return m;
}

// Release
void freeM(int **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

// Add
void add(int **a, int **b, int **c, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
}

// Subtract
void sub(int **a, int **b, int **c, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] - b[i][j];
}

// Strassen
void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {   // Base
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int h = n / 2;
    int **a[4], **b[4], **m[7];
    int **t1 = alloc(h), **t2 = alloc(h);

    for (int i = 0; i < 4; i++) { a[i] = alloc(h); b[i] = alloc(h); }
    for (int i = 0; i < 7; i++) m[i] = alloc(h);

    // Split
    for (int i = 0; i < h; i++)
        for (int j = 0; j < h; j++) {
            a[0][i][j] = A[i][j];         a[1][i][j] = A[i][j + h];
            a[2][i][j] = A[i + h][j];     a[3][i][j] = A[i + h][j + h];
            b[0][i][j] = B[i][j];         b[1][i][j] = B[i][j + h];
            b[2][i][j] = B[i + h][j];     b[3][i][j] = B[i + h][j + h];
        }

    // M1 = (A11 + A22)(B11 + B22)
    add(a[0], a[3], t1, h); add(b[0], b[3], t2, h); strassen(t1, t2, m[0], h);
    // M2 = (A21 + A22) B11
    add(a[2], a[3], t1, h); strassen(t1, b[0], m[1], h);
    // M3 = A11 (B12 - B22)
    sub(b[1], b[3], t2, h); strassen(a[0], t2, m[2], h);
    // M4 = A22 (B21 - B11)
    sub(b[2], b[0], t2, h); strassen(a[3], t2, m[3], h);
    // M5 = (A11 + A12) B22
    add(a[0], a[1], t1, h); strassen(t1, b[3], m[4], h);
    // M6 = (A21 - A11)(B11 + B12)
    sub(a[2], a[0], t1, h); add(b[0], b[1], t2, h); strassen(t1, t2, m[5], h);
    // M7 = (A12 - A22)(B21 + B22)
    sub(a[1], a[3], t1, h); add(b[2], b[3], t2, h); strassen(t1, t2, m[6], h);

    // Combine
    for (int i = 0; i < h; i++)
        for (int j = 0; j < h; j++) {
            C[i][j]         = m[0][i][j] + m[3][i][j] - m[4][i][j] + m[6][i][j];
            C[i][j + h]     = m[2][i][j] + m[4][i][j];
            C[i + h][j]     = m[1][i][j] + m[3][i][j];
            C[i + h][j + h] = m[0][i][j] - m[1][i][j] + m[2][i][j] + m[5][i][j];
        }

    // Cleanup
    for (int i = 0; i < 4; i++) { freeM(a[i], h); freeM(b[i], h); }
    for (int i = 0; i < 7; i++) freeM(m[i], h);
    freeM(t1, h); freeM(t2, h);
}

int main() {
    int n;

    // Input
    printf("Enter n (power of 2: 2, 4, 8): ");
    scanf("%d", &n);

    int **A = alloc(n), **B = alloc(n), **C = alloc(n);

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    // Multiply
    strassen(A, B, C, n);

    // Result
    printf("\nA x B =\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d\t", C[i][j]);
        printf("\n");
    }

    freeM(A, n); freeM(B, n); freeM(C, n);
    return 0;
}

/*
Sample input:
2
1 2
3 4
5 6
7 8

Output:
19 22
43 50
*/
