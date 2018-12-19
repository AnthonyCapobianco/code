// Benchmark for simple tasks C vs C++ using the same device
// GCC and G++

#include <climits>
#include <cstdlib>

#define var auto

foo(int bar)
{
        return bar * 2;
}

int
main()
{
        var x = 10;
        int64_t sum = 0;
        for (int i = 0; i < INT_MAX and (sum + i * i) < INT64_MAX; i++)
        {
                sum += (rand() & 1) ? i : i * i;
        }
}
