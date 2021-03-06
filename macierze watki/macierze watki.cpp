// macierze watki.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include <list>
#include <future>
#include <mutex>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

static const int num_threads = 2;
using namespace std;


 //D = (A*B)*C


class Matrix
{
public:
	int N;
	int** matrix ;
	Matrix(int N1)
	{
		N = N1;
		matrix = new int*[N];
		for (int i = 0; i < N; i++)
			matrix[i] = new int[N];

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = rand() % 5 + 1;
			}
		}

	};
	vector<int> getColumn(int x) { // zwracam vektor z kolumna nr x
		vector<int> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp.push_back(matrix[i][x]);
		}
		return tmp;
	}

	vector<int> getRow(int x) { // zwracam vektor z kolumna nr x
		vector<int> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp.push_back(matrix[x][i]);
		}
		return tmp;
	}
	void showMatrix() {
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	~Matrix();
	//kolumny vektor ? tablica ?
	
	//wiersze



private:

};


Matrix::~Matrix()
{
}

static std::mutex barrier;

void func(vector<int> x, vector<int> y, vector<int> &result) {
	//vector<int> tmp;
	int tmp = 0;
	//std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
	for (int i = 0; i < x.size(); i++)
	{	
		tmp += x[i] * y[i];
		//std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
	}
	
	std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
	result.push_back(tmp);
	//p.set_value(tmp);
}




int main() {
	srand(time(NULL));
	int rows = num_threads, cols = num_threads;
	// generowanie macierzy NxN

	
	Matrix* A = new Matrix(num_threads);
	Matrix* B = new Matrix(num_threads);
	     
	cout << "Matrix A :" << endl;
	A->showMatrix();
	cout << "Matrix b :" << endl;
	B->showMatrix();

	    // int result = 0;
	vector<int> result;

		 thread bum[num_threads * num_threads];
		 int count = 0;
		 for (size_t i = 0; i < num_threads; i++) // w
		 {
			 for (int j = 0; j < num_threads; j++) //k
			 {
				 bum[count] = thread(func, B->getColumn(j), A->getRow(i), std::ref(result));				
				 count++;
			 }
		 }
		
			
		 for (int i = 0; i < num_threads*num_threads; i++)
		 {
			 bum[i].join();
		 }

		 cout << "Wynik A*B :" << endl;
		  count = 0;
			 for (int i2 = 0; i2 < result.size(); i2++)
			 {
				 count ++;
				 cout << result[i2] << " ";
				 if (count == num_threads)
				 {
					 count = 0;
					 cout << endl;
				 }

			 }
	         return 0;

}

