// PP_4th_task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <string>


using namespace std;
vector<vector<double>> matrix_mul(vector<vector<double>> a, vector<vector<double>> b, int n,int condition){

	vector<double> m(n, 0);
	vector<vector<double>> c(n, m);


	if (condition == 0){
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++){
				for (int k = 0; k < n; k++)
					c[i][j] += a[i][k] * b[k][j];
			}
	}

	if (condition == 1){
#pragma omp parallel for
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++){
				for (int k = 0; k < n; k++)
					c[i][j] += a[i][k] * b[k][j];
			}
	}
	return c;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int n = 100;

	vector<double> m(n, 0);
	vector<vector<double>> a(n, m);

	vector<double> m1(n, 0);
	vector<vector<double>> b(n, m1);

	srand(time(NULL));
	for (auto &num : a)
		for (double &el : num)
			el = rand() % 5;

	for (auto &num : b)
		for (double &el : num)
			el = rand() % 5;

/*	for (auto num : a){
		cout << endl;
		for (double el : num)
			cout << el << " ";
	}

	cout << "\n";

	for (auto num : b){
		cout << endl;
		for (double el : num)
			cout << el << " ";
	}*/


	string hint[2] = {
		"without multiprocessing ",
		"with multiprocessing ",
	};

	for (int i = 0; i < 2; i++){
		double start = omp_get_wtime();
		
		vector<vector<double>> ans = matrix_mul(a, b, n,i);

		double end = omp_get_wtime();
		double seconds = (double)(end - start);
		
		/*cout << "answer" << endl;
		for (auto num : ans){
			cout << endl;
			for (double el : num)
				cout << el << " ";
		}

		cout << "\n";*/

		cout << seconds << " seconds " << hint[i] << endl;

	}

	return 0;
}

