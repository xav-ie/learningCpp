#include <cstdint>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "sequential_fibonacci.hpp"
#include "parallel_pointer_fibonacci.hpp"
#include "parallel_future_fibonacci.hpp"

void print_results(std::vector<std::int64_t>& results) {
        for(auto result : results) {
                std::cout << result << " ";
        }
        std::cout << std::endl;
}

void join_threads(std::vector<std::thread>& threads) {
        for(auto& thread : threads) {
                thread.join();
        }
}

int main(int argc, const char * argv[]) {
        const uint64_t num_threads = 32;

        // sequential_fibonacci
        std::vector<std::int64_t> sequential_results(num_threads, 0);
        for(std::int64_t i = 0; i < num_threads; ++i) {
                sequential_results[i] = sequential_fibonacci<std::int64_t, std::uint64_t>(i);
        }
        print_results(sequential_results);

        std::vector<std::thread> threads;

        // parallel implementation using pass-by-pointer
        std::vector<std::int64_t> parallel_pointer_results(num_threads, 0);
        for(std::uint64_t id = 0; id < num_threads; ++id) {
                threads.emplace_back(parallel_pointer_fibonacci<std::int64_t, std::uint64_t>, id, &(parallel_pointer_results[id]));
        }
        print_results(parallel_pointer_results);


        // parallel implementation using future and promise
        threads.clear();
        std::vector<std::future<std::int64_t>> parallel_futures;
        std::vector<std::int64_t> parallel_future_results;
        for(std::uint64_t i = 0; i< num_threads; ++i) {
                std::promise<std::int64_t> promise;
                parallel_futures.emplace_back(promise.get_future());
                threads.emplace_back(parallel_future_fibonacci<std::int64_t, std::uint64_t>, i, std::move(promise));
        }
        join_threads(threads);
        for(auto& parallel_future : parallel_futures) {
                parallel_pointer_results.push_back(parallel_future.get());
        }
        print_results(parallel_future_results);


        return 0;
}
