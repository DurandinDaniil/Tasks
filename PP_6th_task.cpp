// PP_6th_task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string> 
#include <vector>
#include <time.h>
#include <iostream>
#include <omp.h>


using namespace std;




vector<double> matrix_mul(vector<double> a, vector<double> b, int n, int condition) {

	vector<double> c(n*n, 0);

	if (condition == 0){
		int i, j, k;
		for (i = 0; i<n; i++)
			for (j = 0; j<n; j++)
				for (k = 0; k<n; k++)
					c[i*n + j] += a[i*n + k] * b[k*n + j];
	}


	if (condition == 1){
		int i, j, k;
		int NestedThreadsNum = 2;
		omp_set_nested(true);
		omp_set_num_threads(NestedThreadsNum);
#pragma omp parallel for private (j, k)
		for (i = 0; i < n; i++)
#pragma omp parallel for private (k)
			for (j = 0; j < n; j++)
				for (k = 0; k < n; k++)
					c[i*n + j] += a[i*n + k] * b[k*n + j];
	}

	if (condition == 2){
		int ThreadNum = 4;
		int Gridn = int(sqrt((double)ThreadNum));
		int Blockn = n / Gridn;
		omp_set_num_threads(ThreadNum);
#pragma omp parallel
		{
			int ThreadID = omp_get_thread_num();
			int RowIndex = ThreadID / Gridn;
			int ColIndex = ThreadID%Gridn;
			for (int iter = 0; iter<Gridn; iter++) {
				for (int i = RowIndex*Blockn; i<(RowIndex + 1)*Blockn; i++)
					for (int j = ColIndex*Blockn; j<(ColIndex + 1)*Blockn; j++)
						for (int k = iter*Blockn; k<(iter + 1)*Blockn; k++)
							c[i*n + j] += a[i*n + k] * b[k*n + j];
			}
		} 

	}


	return c;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 100;

	vector<double> a(n*n, 2);
	//vector<vector<double>> a(n, m);

	vector<double> b(n*n, 2);
	//vector<vector<double>> b(n, m1);

	srand(time(NULL));
	for (auto &num : a)
			num = rand() % 5;

	for (auto &num : b)
			num = rand() % 5;

	/*for (int i = 0; i < n*n; i++){
		cout << a[i] << " ";
	}

	cout << endl;
	cout << "--------" << endl;*/

	/*for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << a[i*n + j] << " ";
		}
		cout << endl;
	}

	cout << endl;*/

	/*for (int i = 0; i < n*n; i++){
		cout << b[i] << " ";
	}

	cout << endl;
	cout << "--------" << endl;*/

	/*for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << b[i*n + j] << " ";
		}
		cout << endl;
	}*/


	string hint[3] = {
		"without multiprocessing ",
		"with tape algorithm",
		"with block algoritm"
	};
	
	int dim_mass[] = { 50, 100, 150 };

	for (int i = 0; i < 3; i++){

		cout << hint[i] << endl;

		for (int j = 0; j < 3; j++){

			int n = dim_mass[j];

			vector<double> a(n*n, 2);

			vector<double> b(n*n, 2);

			double start = omp_get_wtime();
			vector<double> answer = matrix_mul(a, b, n, i);
			double end = omp_get_wtime();
			double seconds = (double)(end - start);


		cout << seconds << " seconds for " << dim_mass[j] << " dimensions" << endl;
	}
		cout <<"-------------" << endl;

		/*for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				cout << answer[i*n + j] << " ";
			}
			cout << endl;
		}*/

	}

	return 0;
}

