// Assignment 2 - OpenMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <omp.h>
#include <iostream>
#include <vector>

using namespace std;




const int N = 20000;


void applySequential(double** matrix) {

    //Use the formula to fill the matrix
    for (size_t i = 1; i < N; i++)
    {
        for (size_t j = 1; j < N; j++)
        {
            matrix[i][j] = fabs(sin(matrix[i - 1][j - 1])) + fabs(sin(matrix[i][j - 1])) + fabs(sin(matrix[i - 1][j])) * 100;
        }
    }
    //Print the matrix
    /*for (auto& i : matrix)
    {
        std::cout << "\n";
        for (const double j : i)
        {
            std::cout << j << " ";
        }
    }*/
}


void applyParallel(double** matrix) {
        
#pragma omp parallel
    {
        omp_set_num_threads(4);
        //Use the formula to fill the matrix
        #pragma omp parallel for
        for (size_t i = 1; i < N; i++)
        {
            for (size_t j = 1; j < N; j++)
            {
                matrix[i][j] = fabs(sin(matrix[i - 1][j - 1])) + fabs(sin(matrix[i][j - 1])) + fabs(sin(matrix[i - 1][j])) * 100;
            }
        }
    }
    
}

void showResults(double** matrix, int N, int row1, int col1, int row2, int col2, int row3, int col3) {
    cout << "Stencil Operation Results for matrix elements:" << endl;
    cout << "A[" << row1 << "][" << col1 << "]: " << matrix[row1][col1] << endl;
    cout << "A[" << row2 << "][" << col2 << "]: " << matrix[row2][col2] << endl;
    cout << "A[" << row3 << "][" << col3 << "]: " << matrix[row3][col3] << endl;
}

int main(int argc, char** argv)
{
    // Initialize a matrix
    //double matrix[N][M];
    double** parallelMatrix = new double* [N];
    double** sequentialMatrix = new double* [N];


    for (int i = 0; i < N; i++)
    {
        sequentialMatrix[i] = new double[N];
        parallelMatrix[i] = new double[N];

        parallelMatrix[i][0] = 150;
        sequentialMatrix[i][0] = 150;

        parallelMatrix[0][i] = 250;
        sequentialMatrix[0][i] = 250;

    }

    parallelMatrix[0][0] = 0;
    sequentialMatrix[0][0] = 0;


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


    //Start timer
    double start = omp_get_wtime();
    //Call the function
    applyParallel(parallelMatrix);
	//Stop timer
	double end = omp_get_wtime();
    //Print the time
    /*std::cout << "\n\nTime: " << end - start << " seconds\n";*/

    cout << "Execution time for parallel computation: " << end - start << endl;
    showResults(parallelMatrix, N, row1, col1, row2, col2, row3, col3);



    // Sequential time
    start = omp_get_wtime();
    applySequential(sequentialMatrix);
	end = omp_get_wtime();
    //std::cout << "\n\nTime: " << end - start << " seconds\n";
    cout << "Execution time for sequential computation: " << end - start << endl;
    showResults(sequentialMatrix, N, row1, col1, row2, col2, row3, col3);
    
    //std::cout << "Hello World!\n";

    return 0;
}





//Create a function

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
