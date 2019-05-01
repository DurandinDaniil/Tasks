// PP_3rd_task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string> 
#include <vector>
#include <time.h>
#include <iostream>
#include <omp.h>

using namespace std;

double maxmin(vector<vector<double>> a, int n, int condition){

	vector<double> min_v;
	double min = 1001;
	double max = -1;


	if (condition == 0){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (a[i][j] < min){
					min = a[i][j];
				}
			}
			min_v.push_back(min);
			min = 1001;

		}
		for (int i = 0; i < n; i++){
			if (min_v[i] > max){
				max = min_v[i];

			}
		}
	}

	if (condition == 1){
		for (int i = 0; i < n; i++){

#pragma omp parallel for
				for (int j = 0; j < n; j++){
#pragma omp flush(min)
					if (a[i][j] < min){
#pragma omp critical
						if (a[i][j] < min){
							min = a[i][j];
						}
					}
				}
			min_v.push_back(min);
			min = 1001;

		}


#pragma omp parallel for
			for (int i = 0; i < n; i++){
				#pragma omp flush(max)
				if (min_v[i] > max){
#pragma omp critical
					if (min_v[i] > max){
						max = min_v[i];
					}
				}
			}
	}

	return max;
}


int _tmain(int argc, _TCHAR* argv[])
{

	int n = 2000;
	vector<double> m(n, 2);
	vector<vector<double>> a(n,m);

	srand(time(NULL));
	for (auto &num : a)
		for (double &el : num)
			el = rand()%1000;

			
	/*for (auto num : a){
		cout << endl;
		for (double el : num)
			cout << el << " ";
	}

	cout << "\n";
	*/

	string hint[2] = {
		"without multiprocessing ",
		"with multiprocessing ",
	};

	for (int i = 0; i < 2; i++){
		double start = omp_get_wtime();
		float answer = maxmin(a, n, i);
		double end = omp_get_wtime();
		double seconds = (double)(end - start);
		cout << "answer:" << answer << endl;
		cout << seconds << " seconds " << hint[i] << endl;
	}

	return 0;
}

