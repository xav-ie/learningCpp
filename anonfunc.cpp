#include <functional>
#include <iostream>

std::int64_t squared_result(
                std::int64_t x,
                std::int64_t y,
                std::function<std::int64_t()> func
                ) {
        std::int64_t result = func();
        return result * result;
}


int main(int argc, const char * argv[]) {
        int64_t x = 7;
        int64_t y = 13;
        std::int64_t result = squared_result(x,y,[x,y]() {
                        return x+y; });
        std::cout << result << std::endl;
        return 0;
}
