#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <set>


bool cmp (int i,int j) { return (i<j); }


int main()
{
	std::vector <int> vec;
	vec.reserve(100);
	std::set<int> se;


    auto time_0 = std::chrono::steady_clock::now();
    for (int i =0; i<100; i++){
        int a = rand();
        vec[i]= a;
        se.insert(a);
    }

    auto time_1 = std::chrono::steady_clock::now();
    std::sort(vec.begin(), vec.end(), cmp);
    auto time_end = std::chrono::steady_clock::now();



    auto duration_vec = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_1);
    auto duration_se = std::chrono::duration_cast<std::chrono::nanoseconds>(time_1 - time_0);



    std::cout << "The time of sort of vector(std::sort): " << duration_vec.count() << std::endl;
    std::cout << "The time of sort of set: " << duration_se.count() << std::endl;

    //The time of sort of vector is approximately 200 nanoseconds
    //The time of sort of set is approximately 60.000 nanoseconds

	return 0;
}
