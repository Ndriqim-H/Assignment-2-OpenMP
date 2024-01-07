#include <iostream>
#include <cmath>
#include <omp.h>


using namespace std;

int main31(int argc, char* argv[]) {
	
	omp_set_num_threads(4);
	#pragma omp  parallel num_threads(16) 
	{
		int id = omp_get_thread_num();
		cout << "Hello " << " From " << id << endl;
	}
}