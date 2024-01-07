#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

void showResults(float** matrix, int N, int row1, int col1, int row2, int col2, int row3, int col3);

int main2(int argc, char** argv) {
    int N = 10000;
    float** sequentialMatrix = new float* [N];
    float** parallelMatrix = new float* [N];

    for (int i = 0; i < N; i++) {
        sequentialMatrix[i] = new float[N];
        parallelMatrix[i] = new float[N];

        sequentialMatrix[0][i] = 250;
        sequentialMatrix[i][0] = 150;
        parallelMatrix[0][i] = 250;
        parallelMatrix[i][0] = 150;
    }

    sequentialMatrix[0][0] = 0;
    parallelMatrix[0][0] = 0;

    int row1, col1, row2, col2, row3, col3;

    // Check if the program is called with the correct number of arguments
    if (argc != 7) {
        cout << "Usage: " << argv[0] << " row1 col1 row2 col2 row3 col3" << endl;
        return 1;
    }
    auto isValidIndex = [](int index, int limit) {
        return index >= 0 && index < limit;
        };

    // Parse command line arguments
    row1 = atoi(argv[1]);
    col1 = atoi(argv[2]);
    row2 = atoi(argv[3]);
    col2 = atoi(argv[4]);
    row3 = atoi(argv[5]);
    col3 = atoi(argv[6]);

    // Validate indices
    if (!isValidIndex(row1, N) || !isValidIndex(col1, N) ||
        !isValidIndex(row2, N) || !isValidIndex(col2, N) ||
        !isValidIndex(row3, N) || !isValidIndex(col3, N)) {
        cout << "Error: Row or column index out of bounds." << endl;
        return 1;
    }

    double startTime, endTime;

    // Parallel computation
    startTime = omp_get_wtime();
#pragma omp parallel for num_threads(4)
    for (int idx = 1; idx < N * N; idx++) {
        int i = idx / N;
        int j = idx % N;

        if (i >= 1 && j >= 1) {
            parallelMatrix[j][i] = (fabs(sin(parallelMatrix[j - 1][i - 1])) + fabs(sin(parallelMatrix[j][i - 1])) + fabs(sin(parallelMatrix[j - 1][i]))) * 100;
        }
    }
    endTime = omp_get_wtime();

    cout << "Execution time for parallel computation: " << endTime - startTime << endl;
    showResults(parallelMatrix, N, row1, col1, row2, col2, row3, col3);

    // Sequential computation
    startTime = omp_get_wtime();
    for (int idx = 1; idx < N * N; idx++) {
        int i = idx / N;
        int j = idx % N;

        if (i >= 1 && j >= 1) {
            sequentialMatrix[i][j] = (fabs(sin(sequentialMatrix[i - 1][j - 1])) + fabs(sin(sequentialMatrix[i][j - 1])) + fabs(sin(sequentialMatrix[i - 1][j]))) * 100;
        }
    }
    endTime = omp_get_wtime();

    cout << "\nExecution time for sequential computation: " << endTime - startTime << endl;
    showResults(sequentialMatrix, N, row1, col1, row2, col2, row3, col3);

    // Memory cleanup
    for (int i = 0; i < N; i++) {
        delete[] sequentialMatrix[i];
        delete[] parallelMatrix[i];
    }
    delete[] sequentialMatrix;
    delete[] parallelMatrix;

    return 0;
}

void showResults(float** matrix, int N, int row1, int col1, int row2, int col2, int row3, int col3) {
    cout << "Stencil Operation Results for matrix elements:" << endl;
    cout << "A[" << row1 << "][" << col1 << "]: " << matrix[row1][col1] << endl;
    cout << "A[" << row2 << "][" << col2 << "]: " << matrix[row2][col2] << endl;
    cout << "A[" << row3 << "][" << col3 << "]: " << matrix[row3][col3] << endl;
}
