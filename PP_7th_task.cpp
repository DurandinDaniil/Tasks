// PP_7th_task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string> 
#include <vector>
#include <time.h>
#include <iostream>
#include <omp.h>


using namespace std;



int search_substr(const string str, const string substr, int condition)
{
	int result = -1;

	if (condition == 0){
		for (int i = 0; i < str.length() - substr.length() + 1; i++)
		{
			int counter = 0;
			for (int j = 0; j < substr.length(); j++)
			{
				if (str[i + j] != substr[j])
					break;
				counter++;
			}
			if (counter == substr.length())
			{
				result = i;
			}
		}
	}

	if (condition == 1){
#pragma omp parallel shared(str, substr)
{
#pragma omp for
		for (int i = 0; i < str.length() - substr.length() + 1; i++)
		{
			int counter = 0;
			for (int j = 0; j < substr.length(); j++)
			{
				if (str[i + j] != substr[j])
					break;
				counter++;
			}

			if (counter == substr.length())
			{
				//#pragma omp single
				result = i;
				//break;
			}
		}
	}
	}

	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 1000000;
	vector<char> a(n, 0);

	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	srand(time(NULL));
	for (auto &el : a)
		el = alphanum[rand() % (sizeof(alphanum) - 1)];

	string str(a.begin(), a.end());

	string substr(a.end() - 3, a.end());

	//cout << str << endl;
	//cout << substr << endl;

	//for (auto el : a)
	//	cout << el;

	string hint[2] = {
		"without multiprocessing ",
		"with multiprocessing ",
	};

	for (int i = 0; i < 2; i++){
		double start = omp_get_wtime();
		int result = search_substr(str, substr, i);
		double end = omp_get_wtime();
		cout << result << endl;
		double seconds = (double)(end - start);
		cout << seconds << " seconds " << hint[i] << endl;
	}

		
		return 0;
}

