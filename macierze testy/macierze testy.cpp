// macierze testy.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

static std::mutex barrier;

void dot_product(const std::vector<int> &v1, const std::vector<int> &v2, int &result) {
	for (int i = L; i < R; ++i) {
		result += v1[i] * v2[i];	
		std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
	}
}

int main()
{
	int nr_elements = 100000;
	     int nr_threads = 2;
	     int result = 0;
	     std::vector<std::thread> threads;


		 std::vector<int> v1(nr_elements, 1), v2(nr_elements, 2);
		 
			      //Split nr_elements into nr_threads parts
			     
		 
			      //Launch nr_threads threads:
			      for (int i = 0; i < nr_threads; ++i) {
			          threads.push_back(std::thread(dot_product, std::ref(v1), std::ref(v2), std::ref(result)));
			 
					}
		 
			 
			      //Join the threads with the main thread
			      for (auto &t : threads) {
			          t.join();
			 
					}
		 
			      //Print the result
			      std::cout << result << std::endl;


				  return 0;
}

