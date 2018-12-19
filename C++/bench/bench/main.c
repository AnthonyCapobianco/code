// Benchmark for simple tasks C vs C++ using the same device
// GCC and G++

#include <stdlib.h>
#include <limits.h>

int main()
{
        int64_t sum = 0;
        for (int i = 0; i < INT_MAX && (sum + i * i) < INT64_MAX; i++)
        {
                sum += (rand() & 1) ? i : i * i;
        }
}
