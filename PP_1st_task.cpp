// PP_1st_task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>
#include <string>
using namespace std;

typedef float(*pointFunc)(float);


float integral(float x){
	return 4 / (1 + x*x);
}

float rect_integral(pointFunc fun,
	const float a, const float b, const int n, const int condition) {
	float h = fabs((b - a) / n);
	float sum = 0;


	if (condition == 0){
		for (int i = 0; i < n; ++i)
			sum += fun((a + 2*i * h) / 2) * h;
	}

	if (condition == 1){
#pragma omp parallel
	{
		float local_sum = 0;
		#pragma omp for
		for (int i = 0; i < n; ++i){
			local_sum += fun((a + 2 * i * h) / 2) * h;
		}


		#pragma omp atomic
		sum += local_sum;
	}

	}

	if (condition == 2){
#pragma omp parallel reduction (+: sum)
	{
#pragma omp for
		for (int i = 0; i < n; ++i)
			sum += fun((a + 2 * i * h) / 2) * h;
	}

	}
	return sum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string hint[3] = {
		"without parallel",
		"with \'parallel for\'",
		"with \'reduce()\'"
	};

	for (int i = 0; i < 3; i++){
		cout << '\n';
		double start = omp_get_wtime();
		float answer = rect_integral(integral, 0, 1, 500000, i);
		double end = omp_get_wtime();
		double seconds = (double)(end - start);
		cout << "answer:" << answer << endl;
		cout << seconds << " seconds " << hint[i] << endl;
	}

	return 0;
}

