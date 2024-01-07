// Stencil-Code_OpenMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;
void printElements(int argc, char** argv, float** matrix, int N);

int main1(int argc, char** argv)
{
	int N = 20000;
	float** a = new float* [N];
	float** p = new float* [N];

	double start, end;

	for (size_t i = 0; i < N; i++)
	{
		a[i] = new float[N];
		p[i] = new float[N];

		a[0][i] = 250;
		a[i][0] = 150;
		p[0][i] = 250;
		p[i][0] = 150;
	}

	a[0][0] = 0;
	p[0][0] = 0;

	int x1, y1, x2, y2;
	cout << "Enter first element position:" << endl;
	cin >> x1;
	cin >> y1;
	cout << endl << "Enter second element position:" << endl;
	cin >> x2;
	cin >> y2;
	cout << endl;
	int tid;
	start = omp_get_wtime();
	//parallel
	for (int i = 1; i < N; i++)
	{
		#pragma omp parallel for num_threads(4)
		for (int j = i; j >= 1; j--)
		{
			tid = omp_get_thread_num();
			p[j][i - (j - 1)] = (fabs(sin(p[j - 1][i - j])) + fabs(sin(p[j][i - j])) + fabs(sin(p[j - 1][i - (j - 1)]))) * 100;
		}
	}
	for (int i = 2; i < N; i++)
	{
#pragma omp parallel for num_threads(4)
		for (int j = i; j < N; j++)
		{
			tid = omp_get_thread_num();
			//printf("Hello World from thread = %d\n", tid);
			p[j][N - 1 - (j - i)] = (fabs(sin(p[j - 1][N - 2 - (j - i)])) + fabs(sin(p[j][N - 2 - (j - i)])) + fabs(sin(p[j - 1][N - 1 - (j - i)]))) * 100;
		}
	}
	end = omp_get_wtime();


	cout << "Parallel: " << end - start << endl;
	printElements(argc, argv, p, N);
	cout << p[x1][y1] << endl;
	cout << p[x2][y2] << endl << endl;


	start = omp_get_wtime();
	//sequential
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			a[i][j] = (fabs(sin(a[i - 1][j - 1])) + fabs(sin(a[i][j - 1])) + fabs(sin(a[i - 1][j]))) * 100;
		}
	}
	end = omp_get_wtime();
	cout << "Sequential: " << end - start << endl;
	printElements(argc, argv, a, N);

	cout << a[x1][y1] << endl;
	cout << a[x2][y2] << endl;

	/* free(a);
	  free(p);*/

}


void printElements(int argc, char** argv, float** matrix, int N)
{
	if (argc > 1)
	{
		if ((argc - 1) % 2 == 0)
		{
			for (int i = 1; i < argc; i = i + 2)
			{
				int firstIndex = atoi(argv[i]);
				int secondIndex = atoi(argv[i + 1]);

				if (firstIndex < N && secondIndex < N)
				{
					cout << "\nA[" << firstIndex << "][" << secondIndex << "]: " << matrix[firstIndex][secondIndex];
				}
			}
		}
		else {
			cout << "\nArguments number should be even!";
		}
	}

	cout << "\n\n";
}