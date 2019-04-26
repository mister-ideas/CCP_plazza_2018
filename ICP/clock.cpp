#include <iostream>
#include <cstdio>
#include <ctime>
#include <unistd.h>

int main()
{
    std::clock_t clk;
    double duration = 0;

    clk = std::clock();
    std::cout << "Hello" << std::endl;
    while (1) {
        duration = (std::clock() - clk) / (double)(CLOCKS_PER_SEC/1000);
        if (duration == 5000) {
            std::cout << duration << std::endl;
            break;
        }
    }

    return (0);
}
