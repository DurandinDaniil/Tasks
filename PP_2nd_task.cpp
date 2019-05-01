// PP_2nd_task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <string>


using namespace std;

double scalmult(vector<double> a, vector<double> b,int n, int condition)
{


	double sum = 0;

	if (condition == 0){
		for (int i = 0; i < n; i++)
			sum += a[i] * b[i];

	}



	if(condition == 1){
#pragma omp parallel for reduction (+:sum)
		for (int i = 0; i < n; i++)
			sum += a[i] * b[i];
	}

	return sum;
}


int _tmain(int argc, _TCHAR* argv[])
{

	int n = 10000000;
	srand(time(NULL));
	vector<double> a(n, 1+ rand() % 5);
	vector<double> b(n, 1+ rand() % 5);


	string hint[2] = {
			"without multiprocessing ",
			"with multiprocessing ",
		};


	for (int i = 0; i < 2; i++){
		double start = omp_get_wtime();
		float answer = scalmult(a,b,n, i);
		double end = omp_get_wtime();
		double seconds = (double)(end - start);
		cout << "answer:" << answer << endl;
		cout << seconds << " seconds " << hint[i] << endl;
	}


	return 0;
}

