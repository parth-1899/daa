#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long cmp = 0;   // Comparisons

// Swap
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// Partition
int partition(int a[], int l, int r) {
    int pivot = a[r];       // Pivot
    int i = l - 1;
    for (int j = l; j < r; j++) {
        cmp++;              // Count
        if (a[j] < pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[r]);
    return i + 1;
}

// Sort
void quickSort(int a[], int l, int r) {
    if (l < r) {
        int p = partition(a, l, r);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, r);
    }
}

// Best
void buildBest(int a[], int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    buildBest(a, l, mid - 1);
    buildBest(a, mid + 1, r);
    swap(&a[mid], &a[r]);   // Balanced
}

// Measure
long measure(int a[], int n) {
    cmp = 0;
    quickSort(a, 0, n - 1);
    return cmp;
}

int main() {
    int n;

    // Part 1: sort user list
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    quickSort(a, 0, n - 1);
    printf("Sorted: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n\n");
    free(a);

    // Part 2: analysis
    printf("Enter size for analysis (e.g. 1000): ");
    scanf("%d", &n);
    int *b = malloc(n * sizeof(int));

    // Best
    for (int i = 0; i < n; i++) b[i] = i + 1;
    buildBest(b, 0, n - 1);
    long best = measure(b, n);

    // Average
    srand(42);
    for (int i = 0; i < n; i++) b[i] = rand() % 100000;
    long avg = measure(b, n);

    // Worst
    for (int i = 0; i < n; i++) b[i] = i + 1;
    long worst = measure(b, n);

    printf("\nn = %d\n", n);
    printf("Best    : %ld comparisons   (n log n = %.0f)\n", best, n * log2((double)n));
    printf("Average : %ld comparisons   (1.39 n log n = %.0f)\n", avg, 1.39 * n * log2((double)n));
    printf("Worst   : %ld comparisons   (n(n-1)/2 = %ld)\n", worst, (long)n * (n - 1) / 2);

    printf("\nComplexity:\n");
    printf("Best    : O(n log n)\n");
    printf("Average : O(n log n)\n");
    printf("Worst   : O(n^2)\n");

    free(b);
    return 0;
}
