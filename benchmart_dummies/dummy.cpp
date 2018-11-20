#include <iostream>
#include <chrono>

static inline int throwaway(const int useless) {
  int throwawayLong = 1337;
  for (int i = 0; i < 10000; ++i) {
    throwawayLong += i;
  }
  return throwawayLong;
}

int main() {
  using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
    std::chrono::high_resolution_clock,
    std::chrono::steady_clock>;

  const auto startTime = Clock::now();
  std::cout << throwaway(0xDEADBABE) << std::endl;
  const auto endTime = Clock::now();
   
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << std::endl;
}
