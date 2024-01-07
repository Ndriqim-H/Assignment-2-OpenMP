#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;
const int N = 20000;

void stencilOperation(float** A) {
    // Initialize the first column, first row, and first element of the matrix
    for (int i = 0; i < N; i++) {
        A[i] = new float[N];
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

void showResults(float** matrix, int row1, int col1, int row2, int col2, int row3, int col3) {
    cout << "Stencil Operation Results for matrix elements:" << endl;
    cout << "A[" << row1 << "][" << col1 << "]: " << matrix[row1][col1] << endl;
    cout << "A[" << row2 << "][" << col2 << "]: " << matrix[row2][col2] << endl;
    cout << "A[" << row3 << "][" << col3 << "]: " << matrix[row3][col3] << endl;
}

int main1(int argc, char** argv) {
    float** A = new float* [N];

    // Perform the stencil operation on the matrix A
    stencilOperation(A);

    // Print the resulting matrix A
    /*for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.3f\t", A[i][j]);
        }
        printf("\n");
    }*/

    int row1, col1, row2, col2, row3, col3;
    // Parse command line arguments
    row1 = atoi(argv[1]);
    col1 = atoi(argv[2]);
    row2 = atoi(argv[3]);
    col2 = atoi(argv[4]);
    row3 = atoi(argv[5]);
    col3 = atoi(argv[6]);
    auto isValidIndex = [](int index, int limit) {
        return index >= 0 && index < limit;
        };
    // Validate indices
    if (!isValidIndex(row1, N) || !isValidIndex(col1, N) ||
        !isValidIndex(row2, N) || !isValidIndex(col2, N) ||
        !isValidIndex(row3, N) || !isValidIndex(col3, N)) {
        cout << "Error: Row or column index out of bounds." << endl;
        return 1;
    }

    showResults(A, row1, col1, row2, col2, row3, col3);


    return 0;
}



