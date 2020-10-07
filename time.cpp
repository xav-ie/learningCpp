#include <iostream>
#include <chrono>
 
int main()
{
    using namespace std::chrono_literals;
    auto halfmin = 30s;
    std::cout << "half a minute is " << halfmin.count() << " seconds\n"
              << "a minute and a second is " << (1min + 1s).count() << " seconds\n";
}
