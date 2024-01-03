// Assignment 2 - OpenMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <omp.h>
#include <iostream>
#include <vector>

const int N = 10000;
const int M = 10000;

void applySequential(std::vector<std::vector<double>> matrix) {

    //Use the formula to fill the matrix
    for (size_t i = 1; i < N; i++)
    {
        for (size_t j = 1; j < M; j++)
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


void applyParallel(std::vector<std::vector<double>> matrix) {
        
#pragma omp parallel
    {
        omp_set_num_threads(4);
        //Use the formula to fill the matrix
        #pragma omp parallel for
        for (size_t i = 1; i < N; i++)
        {
            for (size_t j = 1; j < M; j++)
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
    
}
int main()
{
    // Initialize a matrix
    //double matrix[N][M];
    std::vector<std::vector<double>> matrix(N, std::vector<double>(M, 0));

    for (int i = 0; i < N; i++)
    {
        matrix[i][0] = 150;
    }

    for (int i = 0; i < N; i++)
    {
        matrix[0][i] = 250;
    }
    matrix[0][0] = 0;


    //Start timer
    double start = omp_get_wtime();
    //Call the function
    applyParallel(matrix);
	//Stop timer
	double end = omp_get_wtime();
    //Print the time
    std::cout << "\n\nTime: " << end - start << " seconds\n";

    // Sequential time
    start = omp_get_wtime();
    applySequential(matrix);
	end = omp_get_wtime();
    std::cout << "\n\nTime: " << end - start << " seconds\n";
    
    
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
