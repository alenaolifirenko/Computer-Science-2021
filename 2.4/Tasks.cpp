#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <numeric>
#include <functional>
#include <chrono>
#include <random>


bool prime(int n) {
    if (n < 0) n *= (-1);
    if (n == 0 || n == 1)
        return false;
    for (int i = 2; i <= n/2; i++)
        if (n % i == 0)
            return false;
    return true;
}
bool cmp(int i, int j) { return (i > j); }


int main()
{
    std::vector <int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //Create P1

    for (int i = 0; i < 2; i++)
    {
        int a;
        std::cin >> a;
        v.push_back(a);
    } //Add several v[i]

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(v), std::end(v), std::default_random_engine(seed));
    //Randomly rearrange elements in range

    std::sort(std::begin(v), std::end(v));
    v.erase(std::unique(std::begin(v), std::end(v)), std::end(v));
    //Remove consecutive duplicates in range

    auto result = std::count_if(std::begin(v), std::end(v), [](auto x) {return ((x%2) == 1); });
    std::cout << result<< " -number of x%2 !=0" << std::endl;
    //Number of x%2 !=0


    auto [min, max] = std::minmax_element(std::begin(v), std::end(v));
    std::cout << *min << ' ' << *max << " -min and max" << std::endl;
    // min and max of P1

    auto it = std::find_if(std::begin(v), std::end(v), [](auto x) {return prime(x); });
    if (it != std::end(v)) { std::cout << std::endl << *it << " -prime number"<< std::endl; }
    //Prime number

    std::transform(std::begin(v), std::end(v), std::begin(v), [](auto x) {return x*x; });
    //Change x to x^2

    std::vector <int> v1(12);
    std::default_random_engine dre;
    std::uniform_int_distribution <> uid(-100, 100);
    std::generate_n(std::begin(v1), 12, [&dre, &uid]() {return uid(dre); });
    //Create P2

    int sum = 0;
    std::for_each(std::begin(v1), std::end(v1), [&sum](auto x) {sum +=x;});
    auto s = std::accumulate(std::begin(v1), std::end(v1), 0);
    std::cout << sum << " or " << s << " -sum"<< std::endl;
    //Sum

    std::fill_n(std::begin(v1), 3, 1);
    // v1[0], v1[1], v1[2] -> 1

    std::vector <int> v2(12);
    std::transform(std::begin(v), std::end(v), std::begin(v1), std::begin(v2), std::minus <int>());
    //Create P3

    std::replace_if(std::begin(v2), std::end(v2), [](auto x) {return (x < 0); }, 0);
    //-n -> 0

    v2.erase(std::remove_if(std::begin(v2), std::end(v2), [](auto x) {return x == 0; }), std::end(v2));
    //Delete 0

    std::reverse(std::begin(v2), std::end(v2));
    // i -> n-i

    std::nth_element(std::begin(v2), std::next(std::begin(v2), 2), std::end(v2), cmp);
    std::cout << v2[0] << ' ' << v2[1] << ' ' << v2[2] << std::endl;
    // 3 max

    std::sort(std::begin(v), std::end(v));
    std::sort(std::begin(v1), std::end(v1));
    //Sort P1 and P2

    std::vector<int> v3 (24);
    std::merge(std::begin(v), std::end(v), std::begin(v1), std::end(v1), std::begin(v3));
    //Union of two sorted ranges: P1 and P2

    auto [x1, x2] = std::equal_range(std::begin(v3), std::end(v3), 1);
    std::cout << "bounds at positions " << (x1 - std::begin(v3)) << " and " << (x2 - std::begin(v3)) << '\n';
    //where add 1

    std::cout << std::endl << "P1" << std::endl;
    std::for_each(std::begin(v), std::end(v), [](auto x) {std::cout << x << ' '; });
    std::cout << std::endl << "P2" << std::endl;
    std::for_each(std::begin(v1), std::end(v1), [](auto x) {std::cout << x << ' '; });
    std::cout << std::endl << "P3" << std::endl;
    std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << ' '; });
    std::cout << std::endl << "P4" << std::endl;
    std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << ' '; });
    //Write



    return 0;
}
