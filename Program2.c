#include <stdio.h>
 
#define MAX 50
 
struct Term {
    int row, col, val;
};
 
// Read a sparse matrix in triplet form (row, col, value) for non-zero elements
void readSparse(struct Term arr[], int *rows, int *cols, int *n) {
    printf("Enter rows, columns and number of non-zero elements: ");
    scanf("%d %d %d", rows, cols, n);
    printf("Enter each non-zero element as: row col value\n");
    for (int i = 0; i < *n; i++) {
        scanf("%d %d %d", &arr[i].row, &arr[i].col, &arr[i].val);
    }
}
 
// Display sparse matrix in triplet form
void display(struct Term arr[], int rows, int cols, int n) {
    printf("Size: %dx%d, Non-zero terms: %d\n", rows, cols, n);
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", arr[i].row, arr[i].col, arr[i].val);
}
 
// Transpose: swap row and col, then sort by row (then col) for correct order
void transpose(struct Term a[], int rows, int cols, int n, struct Term t[]) {
    for (int i = 0; i < n; i++) {
        t[i].row = a[i].col;
        t[i].col = a[i].row;
        t[i].val = a[i].val;
    }
    // simple bubble sort on (row, col)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (t[j].row > t[j + 1].row ||
               (t[j].row == t[j + 1].row && t[j].col > t[j + 1].col)) {
                struct Term temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
}
 
// Addition: both matrices must have same size; inputs assumed sorted by row, col
int addSparse(struct Term a[], int na, struct Term b[], int nb, struct Term sum[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i].row == b[j].row && a[i].col == b[j].col) {
            sum[k].row = a[i].row;
            sum[k].col = a[i].col;
            sum[k].val = a[i].val + b[j].val;
            k++; i++; j++;
        } else if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            sum[k++] = a[i++];
        } else {
            sum[k++] = b[j++];
        }
    }
    while (i < na) sum[k++] = a[i++];
    while (j < nb) sum[k++] = b[j++];
    return k;
}
 
int main() {
    struct Term A[MAX], B[MAX], Sum[MAX], T[MAX];
    int rA, cA, nA, rB, cB, nB, nSum;
 
    printf("--- Enter Matrix A ---\n");
    readSparse(A, &rA, &cA, &nA);
 
    printf("\n--- Enter Matrix B ---\n");
    readSparse(B, &rB, &cB, &nB);
 
    printf("\nMatrix A:\n");
    display(A, rA, cA, nA);
 
    printf("\nMatrix B:\n");
    display(B, rB, cB, nB);
 
    if (rA == rB && cA == cB) {
        nSum = addSparse(A, nA, B, nB, Sum);
        printf("\nSum of A and B:\n");
        display(Sum, rA, cA, nSum);
    } else {
        printf("\nAddition not possible: dimensions differ.\n");
    }
 
    transpose(A, rA, cA, nA, T);
    printf("\nTranspose of A:\n");
    display(T, cA, rA, nA);
 
    return 0;
}
