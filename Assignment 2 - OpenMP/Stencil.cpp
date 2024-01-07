#include <stdio.h>
#include <math.h>

#define N  10

void stencilOperation(float A[N][N]) {
    // Initialize the first column, first row, and first element of the matrix
    for (int i = 0; i < N; i++) {
        A[i][0] = 150.0;
        A[0][i] = 250.0;
    }
    A[0][0] = 0.0;

    // Perform the stencil operation
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            float term1 = fabs(sin(A[i - 1][j - 1]));
            float term2 = fabs(sin(A[i - 1][j]));
            float term3 = fabs(sin(A[i][j - 1]));

            A[i][j] = (term1 + term2 + term3) * 100;
        }
    }
}

int main1() {
    float A[N][N];

    // Perform the stencil operation on the matrix A
    stencilOperation(A);

    // Print the resulting matrix A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f\t", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}
