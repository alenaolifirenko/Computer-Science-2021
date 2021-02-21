#include <algorithm>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>


bool cmp (int i,int j) { return (i<j); }


int main()
{
	std::vector <int> vec;
	vec.reserve(100);
	std::array<int, 100> arr;
	std::deque<int> deq (100);
	std::list<int> li;
	std::forward_list<int> fli;


    for (int i =0; i<100; i++){
        int a = rand();
        vec[99 - i]= a;
        arr[99-i]=a;
        deq[99-i]=a;
        li.push_front(a);
        fli.push_front(a);

    }


    auto time_0 = std::chrono::steady_clock::now();
    fli.sort();
    auto time_1 = std::chrono::steady_clock::now();
	li.sort();
	auto time_2 = std::chrono::steady_clock::now();


    std::sort(vec.begin(), vec.end(), cmp);
    auto time_3 = std::chrono::steady_clock::now();
	std::sort(arr.begin(), arr.end(), cmp);
	auto time_4 = std::chrono::steady_clock::now();
	std::sort(deq.begin(), deq.end(), cmp);
	auto time_5 = std::chrono::steady_clock::now();

    auto duration_fli = std::chrono::duration_cast<std::chrono::nanoseconds>(time_1 - time_0);
    auto duration_li = std::chrono::duration_cast<std::chrono::nanoseconds>(time_2 - time_1);
    auto duration_vec = std::chrono::duration_cast<std::chrono::nanoseconds>(time_3 - time_2);
    auto duration_arr = std::chrono::duration_cast<std::chrono::nanoseconds>(time_4 - time_3);
    auto duration_deq = std::chrono::duration_cast<std::chrono::nanoseconds>(time_5 - time_4);

    std::cout << "The time of sort of array(std::sort): " << duration_arr.count() << std::endl;
    std::cout << "The time of sort of vector(std::sort): " << duration_vec.count() << std::endl;
    std::cout << "The time of sort of deque(std::sort): " << duration_deq.count() << std::endl;
    std::cout << "The time of sort of list(method): " << duration_li.count() << std::endl;
    std::cout << "The time of sort of forward_list(method): " << duration_fli.count() << std::endl;
    /* —ама€ быстрый результат у вектора - 100-200 наносекунда,
    сама€ медленна€ сортировка у листа - 70-80 тыс наносекунд*/

	return 0;
}
