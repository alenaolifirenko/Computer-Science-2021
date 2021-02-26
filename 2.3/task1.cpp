#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <set>


bool cmp(int i, int j) { return (i < j); }


int main()
{
    std::vector <int> v;
    std::vector <int> vec;
    std::vector <int> vec1;
    std::vector <int> vec2;

    std::set<int> se;
    std::set<int> se1;
    std::set<int> se2;



    for (int i = 0; i < 100000; i++) {
        int a = rand();
        v.push_back(a);
    }


    auto time_0 = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; i++) {

        se.insert(v[i]);
    }

    auto time_1 = std::chrono::steady_clock::now();

    for (int i = 0; i < 10; i++) {

        se1.insert(v[i]);
    }

    auto time_2 = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {

        se2.insert(v[i]);
    }

    auto time_3 = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; i++) {
        vec.push_back(v[i]);
    }

    std::sort(vec.begin(), vec.end(), cmp);

    auto time_4 = std::chrono::steady_clock::now();

    for (int i = 0; i < 10; i++) {
        vec1.push_back(v[i]);
    }

    std::sort(vec1.begin(), vec1.end(), cmp);

    auto time_5 = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        vec2.push_back(v[i]);
    }

    std::sort(vec2.begin(), vec2.end(), cmp);

    auto time_6 = std::chrono::steady_clock::now();


    auto duration_vec = std::chrono::duration_cast<std::chrono::microseconds>(time_4 - time_3);
    auto duration_vec1 = std::chrono::duration_cast<std::chrono::microseconds>(time_5 - time_4);
    auto duration_vec2 = std::chrono::duration_cast<std::chrono::microseconds>(time_6 - time_5);

    auto duration_se = std::chrono::duration_cast<std::chrono::microseconds>(time_1 - time_0);
    auto duration_se1 = std::chrono::duration_cast<std::chrono::microseconds>(time_2 - time_1);
    auto duration_se2 = std::chrono::duration_cast<std::chrono::microseconds>(time_3 - time_2);

    std::cout << "n=10" << std::endl;
    std::cout << "The time of sort of vector(std::sort): " << duration_vec1.count() << std::endl;
    std::cout << "The time of sort of set: " << duration_se1.count() << std::endl << std::endl;

    std::cout << "n=100" << std::endl;
    std::cout << "The time of sort of vector(std::sort): " << duration_vec.count() << std::endl;
    std::cout << "The time of sort of set: " << duration_se.count() << std::endl << std::endl;

    std::cout << "n=100000" << std::endl;
    std::cout << "The time of sort of vector(std::sort): " << duration_vec2.count() << std::endl;
    std::cout << "The time of sort of set: " << duration_se2.count() << std::endl << std::endl;


	return 0;
}

/* RESULTS
n=10
The time of sort of vector(std::sort): 14
The time of sort of set: 31

n=100
The time of sort of vector(std::sort): 132
The time of sort of set: 368

n=100000
The time of sort of vector(std::sort): 276976
The time of sort of set: 407127


*/
