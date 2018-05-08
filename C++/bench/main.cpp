// Benchmark for simple tasks C vs C++ using the same device
// GCC and G++

#include <iostream>
#include <climits>
#include <cstdlib>

int
main()
{
        int64_t sum = 0;
        for (int i = 0; i < INT_MAX and (sum + i * i) < INT64_MAX; i++)
        {
                sum += (rand() & 1) ? i : i * i;
        }
        
        std::cout << sum << std::endl;
}
