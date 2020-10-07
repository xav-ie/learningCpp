#include <iostream>
#include <thread>
#include <mutex>
#include <cstdint>
#include <vector>

std::mutex stdout_mutex;

void say_hello(uint64_t id) {
        std::lock_guard<std::mutex> guard(stdout_mutex);
        std::cout << "Hello from thread: " << id << std::endl;
}

int main(int argc, char * argv[]) {
        const uint64_t num_threads = 4;
        std::vector<std::thread> threads;
        // for all threads
        for(uint64_t id = 0; id < num_threads; id++) {
                // emplace the thread object in vector threads
                // using argument forwarding, this avoids unecessary
                // move operations to the vector after thread creation
                // call say_hello with id

                // won't work because you can't just push on an object
                //std::thread thread(say_hello, id);
                //threads.push_back(thread);
                //thread.start();
                
                // pushes and calls constructor for a thread
                threads.emplace_back(say_hello, id);
        }
        for(auto &thread: threads) {
                thread.join();
        }
        return 0;
}
