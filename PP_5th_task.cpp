// PP_5th_task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string> 
#include <vector>
#include <time.h>
#include <iostream>
#include <omp.h>


using namespace std;


vector<double> ParallelResultCalculation(vector<double> a, vector<double>b, int n, int condition) {
	
	vector<double> c(n, 0);


	if (condition == 0){
		int i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				c[i] += a[i*n + j] * b[j];
		}
	}

	if (condition == 1){
		int i, j;
#pragma omp parallel for private (j)
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				c[i] += a[i*n + j] * b[j];
		}

	}

	if (condition == 2){
		int i, j;
		for (i = 0; i < n; i++) {
#pragma omp parallel for
			for (j = 0; j < n; j++)
				c[i] += a[i*n + j] * b[j];
		}

	}

	if (condition == 3){
		int NestedThreadsNum = 2;
		omp_set_num_threads(NestedThreadsNum);
		omp_set_nested(true);
#pragma omp parallel for
		for (int i = 0; i < n; i++) {
			double ThreadResult = 0;
#pragma omp parallel for reduction(+:ThreadResult)
			for (int j = 0; j < n; j++)
				ThreadResult += a[i*n + j] * b[j];
			c[i] = ThreadResult;
		}
	}

	return c;
}

int _tmain(int argc, _TCHAR* argv[])
{

	int n = 2;

	vector<double> a(n*n, 2);
	//vector<vector<double>> a(n, m);

	vector<double> b(n, 2);
	//vector<vector<double>> b(n, m1);

	srand(time(NULL));
	for (auto &num : a)
		num = rand() % 5;

	for (auto &num : b)
		num = rand() % 5;

	/*for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << a[i*n + j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++){
		cout << b[i] << " ";
	}

	cout << endl;*/

	string hint[4] = {
		"without multiprocessing ",
		"with line data separation",
		"with column data separation",
		"with block algoritm"
	};

	int dim_mass[] = { 250, 500, 1000};
	for (int i = 0; i < 4; i++){

		cout << hint[i] << endl;

		for (int j = 0; j < 3; j++){

			int n = dim_mass[j];

			vector<double> a(n*n, 2);
			//vector<vector<double>> a(n, m);

			vector<double> b(n, 2);

			double start = omp_get_wtime();
			vector<double> answer = ParallelResultCalculation(a, b, n, i);
			double end = omp_get_wtime();
			double seconds = (double)(end - start);


			cout << seconds << " seconds for " << dim_mass[j] << " dimensions" << endl;
		}
		cout << "-------------" << endl;
	}

	return 0;
}

