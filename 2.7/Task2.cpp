#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>

class Threads_Guard
{
public:

    explicit Threads_Guard(std::vector < std::thread >& threads) :
        m_threads(threads)
    {}

    Threads_Guard(Threads_Guard const&) = delete;

    Threads_Guard& operator=(Threads_Guard const&) = delete;

    ~Threads_Guard() noexcept
    {
        try
        {
            for (auto& m_thread : m_threads)
            {
                if (m_thread.joinable())
                {
                    m_thread.join();
                }
            }
        }
        catch (...)
        {
        }
    }

private:

    std::vector < std::thread >& m_threads;
};

template < typename Iterator, typename T >
struct accumulate_block
{
    T operator()(Iterator first, Iterator last)
    {
        return std::accumulate(first, last, T());
    }
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, std::size_t num_threads = 4)
{
    const std::size_t length = std::distance(first, last);

    if (!length)
        return init;

    const std::size_t block_size = length / num_threads;

    std::vector < std::future < T > > futures(num_threads - 1);
    std::vector < std::thread >		  threads(num_threads - 1);

    Threads_Guard guard(threads);

    Iterator block_start = first;

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        std::packaged_task < T(Iterator, Iterator) > task{
                accumulate_block < Iterator, T >() };

        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_start, block_end);

        block_start = block_end;
    }

    T last_result = accumulate_block < Iterator, T >()(block_start, last);

    T result = init;

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        result += futures[i].get();
    }

    result += last_result;

    return result;
}

int main() {
    auto vec_size = 10000000;
    auto size_vec_number_threads = 25;

    std::vector < int > v(vec_size);

    std::iota(v.begin(), v.end(), 1);

    std::vector<std::size_t> number_threads(size_vec_number_threads);
    std::iota(number_threads.begin(), number_threads.end(), 1);


    for (auto n_threads : number_threads) {
        std::cout << n_threads << " ";
        auto time_0 = std::chrono::steady_clock::now();
        parallel_accumulate(v.begin(), v.end(), 0, n_threads);
        auto time_1 = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_1 - time_0);
        std::cout << duration.count() << std::endl;
    }
    return 0;
    /*График - task2.png
    Количество потоков в моем процессоре - 4, поэтому около 4 наблюдается минимум времени.
    При увеличении потоков время несильно флуктурирует, скорее всего, дело в оптимизации. */
}
