#include <iostream>
#include <thread>
#include <future>
#include <random>
#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>



class Threads_Guard
{
public:

    explicit Threads_Guard(std::vector < std::thread > & threads) :
            m_threads(threads)
    {}

    Threads_Guard			(Threads_Guard const&) = delete;

    Threads_Guard& operator=(Threads_Guard const&) = delete;

    ~Threads_Guard() noexcept
    {
        try
        {
            for (auto & m_thread : m_threads)
            {
                if (m_thread.joinable())
                {
                    m_thread.join();
                }
            }
        }
        catch (...)
        {        }
    }

private:

    std::vector < std::thread > & m_threads;
};

double counting_pi (int number_points = 1000000) {

    std::mt19937_64 mersenne (std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> real_dist(-1.0, 1.0);

    int number_points_in_circle = 0;

    double x, y;
    for (int i = 0; i < number_points; ++i) {
        x = real_dist(mersenne);
        y = real_dist(mersenne);
       if (x * x + y * y < 1) number_points_in_circle++;
    }

    return 4.0 * number_points_in_circle / number_points;
}



int count_points(int number_points) {

    std::mt19937_64 mersenne (std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> real_dist(-1.0, 1.0);

    int number_points_in_circle = 0;
    double x, y;

    for (int i = 0; i < number_points; ++i) {
        x = real_dist(mersenne);
        y = real_dist(mersenne);
        if (x * x + y * y < 1) number_points_in_circle++;
    }

    return number_points_in_circle;
}



double parallel_counting_pi (int number_points = 1000000) {

    const int min_per_thread = 100000;
    const int max_threads = number_points / min_per_thread;

    const int hardware_threads = std::thread::hardware_concurrency();

    const int num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    const int block_size = number_points / num_threads;

    std::vector < std::future < int > > futures(num_threads - 1);
    std::vector < std::thread >		  threads(num_threads - 1);

    Threads_Guard guard(threads);

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {

        std::packaged_task < int(int) > task{ count_points };

        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_size);

    }

    int last_result = count_points(block_size);

    int result = 0;

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        result += futures[i].get();
    }

    result += last_result;

    return 4.0 * result / number_points;

}

int main () {

    auto time_0 = std::chrono::steady_clock::now();
    double pi1 = counting_pi();
    auto time_1 = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time_1 - time_0);
    std::cout <<"pi: "<< pi1 << " time in microseconds: " << duration.count();
    
    std::cout << std::endl;
    
    auto time_2 = std::chrono::steady_clock::now();
    double pi2 = parallel_counting_pi();
    auto time_3 = std::chrono::steady_clock::now();
    auto parallel_duration = std::chrono::duration_cast<std::chrono::microseconds>(time_3 - time_2);
    std::cout <<"pi: "<< pi2 << " time in microseconds: " << parallel_duration.count();
    
    /* Results:
    pi: 3.14274 time in microseconds: 1583072                                                                                                 
    pi: 3.14323 time in microseconds: 1805902   */

    return 0;
}

