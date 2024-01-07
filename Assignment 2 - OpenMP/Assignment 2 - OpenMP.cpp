// Assignment 2 - OpenMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iomanip>
#include <omp.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const double epsilon = 1e-9;


const int N = 20000;

void applySequential(float** matrix) {

	//Use the formula to fill the matrix
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			float term1 = fabs(sin(matrix[i - 1][j - 1]));
			float term2 = fabs(sin(matrix[i - 1][j]));
			float term3 = fabs(sin(matrix[i][j - 1]));

			matrix[i][j] = (term1 + term2 + term3) * 100;
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


void applyParallel(float** matrix, int numberOfThreads) {
	//    omp_set_num_threads(8);
	//#pragma omp parallel
	{

		//Use the formula to fill the matrix
#pragma omp parallel for num_threads(numberOfThreads)
/*for (int i = 1; i < N; i++)
{
	for (size_t j = 1; j < N; j++)
	{
		matrix[i][j] = fabs(sin(matrix[i - 1][j - 1])) + fabs(sin(matrix[i][j - 1])) + fabs(sin(matrix[i - 1][j])) * 100;
	}
}*/

		for (int i = 1; i < N; i++) {
			for (int j = 1; j < N; j++) {
				float term1 = fabs(sin(matrix[i - 1][j - 1]));
				float term2 = fabs(sin(matrix[i - 1][j]));
				float term3 = fabs(sin(matrix[i][j - 1]));

				matrix[i][j] = (term1 + term2 + term3) * 100;
			}
		}
	}

}

void showResults(float** matrix, int N, int row1, int col1, int row2, int col2, int row3, int col3, float v1, float v2, float v3) {

	cout << "Stencil Operation Results for matrix elements:" << "\n";
	float u1 = matrix[row1][col1];
	float u2 = matrix[row2][col2];
	float u3 = matrix[row3][col3];

	string res1 = std::abs(u1 - v1) < epsilon ? "Ok" : "Not ok";
	string res2 = std::abs(u2 - v2) < epsilon ? "Ok" : "Not ok";
	string res3 = std::abs(u3 - v3) < epsilon ? "Ok" : "Not ok";

	cout << "A[" << row1 << "][" << col1 << "]: " << u1 << " - " << res1 << "\n";
	cout << "A[" << row2 << "][" << col2 << "]: " << u2 << " - " << res2 << "\n";
	cout << "A[" << row3 << "][" << col3 << "]: " << u3 << " - " << res3 << "\n";

}

int main(int argc, char** argv)
{
	// Initialize a matrix
	//double matrix[N][M];

	int max_thread_count = omp_get_max_threads();
	int available_processors = omp_get_num_procs();
	cout << "Available processors: " << available_processors << "\n";
	cout << "Number of threads: " << max_thread_count << "\n";
	cout << "Stencil Operation Results for matrix elements with size: " << N << "x" << N << "\n=================================\n";

	float** parallelMatrix = new float* [N];
	float** sequentialMatrix = new float* [N];


	for (int i = 0; i < N; i++)
	{
		sequentialMatrix[i] = new float[N];
		parallelMatrix[i] = new float[N];

		parallelMatrix[i][0] = 150;
		sequentialMatrix[i][0] = 150;

		parallelMatrix[0][i] = 250;
		sequentialMatrix[0][i] = 250;

	}

	parallelMatrix[0][0] = 0;
	sequentialMatrix[0][0] = 0;



	// Parse command line arguments
	const int row1 = atoi(argv[1]);
	const int col1 = atoi(argv[2]);
	const int row2 = atoi(argv[3]);
	const int col2 = atoi(argv[4]);
	const int row3 = atoi(argv[5]);
	const int col3 = atoi(argv[6]);
	auto is_valid_index = [](const int index, const int limit) {
		return index >= 0 && index < limit;
		};
	// Validate indices
	if (!is_valid_index(row1, N) || !is_valid_index(col1, N) ||
		!is_valid_index(row2, N) || !is_valid_index(col2, N) ||
		!is_valid_index(row3, N) || !is_valid_index(col3, N)) {
		cout << "Error: Row or column index out of bounds." << "\n";
		return 1;
	}

	// Sequential time
	double start = omp_get_wtime();
	applySequential(sequentialMatrix);
	double end = omp_get_wtime();
	//std::cout << "\n\nTime: " << end - start << " seconds\n";
	const double t_sequential = end - start;
	cout << "Execution time for sequential computation: " << t_sequential
		<< "\n";
	//showResults(sequentialMatrix, N, row1, col1, row2, col2, row3, col3);

	cout << "Stencil Operation Results for matrix elements:" << "\n";
	float v1 = sequentialMatrix[row1][col1];
	float v2 = sequentialMatrix[row2][col2];
	float v3 = sequentialMatrix[row3][col3];

	cout << "A[" << row1 << "][" << col1 << "]: " << v1 << "\n";
	cout << "A[" << row2 << "][" << col2 << "]: " << v2 << "\n";
	cout << "A[" << row3 << "][" << col3 << "]: " << v3 << "\n";

	int number_of_threads = 1;

	while (true)
	{

		if (number_of_threads > max_thread_count)
		{
			number_of_threads = max_thread_count;



			//break;
		}
		start = omp_get_wtime();
		applyParallel(parallelMatrix, number_of_threads);
		end = omp_get_wtime();

		const double t_parallel = end - start;

		if (number_of_threads == 1)
		{
			cout << "\nExecution time for parallel computation with " << number_of_threads << " thread: "
				<< t_parallel
				<< "\n";
		}
		else
		{
			cout << "\nExecution time for parallel computation with " << number_of_threads << " threads: "
				<< t_parallel
				<< "\n";
		}

		showResults(parallelMatrix, N, row1, col1, row2, col2, row3, col3, v1, v2, v3);


		const double speed_up = static_cast<double>(t_sequential) / t_parallel;
		string is_ok = speed_up > number_of_threads * 0.7 ? " Ok " : " Not ok ";
		//cout << "Speed up: " << speed_up << is_ok << "\n";
		string comp = (speed_up > number_of_threads * 0.7 ?
			"(>= " : "(< ") + to_string(number_of_threads * 0.7) + ")";
		//cout << "Speed up: " << speed_up << " " << comp << "=================================\n";

		cout << "Speedup: " << fixed << setprecision(7) << speed_up
			<< is_ok << comp << "\n=================================";


		if (number_of_threads == max_thread_count)
		{
			break;
		}
		number_of_threads *= 2;
	}

	//   //Start timer
	//   start = omp_get_wtime();
	//   //Call the function
	//   applyParallel(parallelMatrix, x);
	   ////Stop timer
	   //end = omp_get_wtime();
	//   //Print the time
	//   /*std::cout << "\n\nTime: " << end - start << " seconds\n";*/

	//   cout << "Execution time for parallel computation with " << x << " threads: " << end - start << endl;

	//   showResults(parallelMatrix, N, row1, col1, row2, col2, row3, col3);





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
