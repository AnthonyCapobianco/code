#include <iostream>
#include <cstdint>

class SplittableUint64 {
private:
  uint32_t h;
  uint32_t l;
  
public:
  SplittableUint64(uint32_t hi, uint32_t lo) noexcept(true)
  : h(hi)
  , l(lo) 
  {
  }
  
  SplittableUint64(uint64_t big) noexcept(true) 
  : h(static_cast<uint32_t> (big >> 32))
  , l(static_cast<uint32_t> (big & 0x0000'0000'ffff'ffff)) 
  {
  }

  uint32_t get_h() const noexcept(true) {
    return h;
  }
  
  uint32_t get_l() const noexcept(true) {
    return l;
  }
  
  uint64_t get_a() const noexcept(true) {
    return l + (static_cast<uint64_t> (h) << 32);
  }
  
};

bool operator==(const SplittableUint64& lhs, const SplittableUint64& rhs) {
  return lhs.get_h() == rhs.get_h() and lhs.get_l() == rhs.get_l();
}

int main() {
  uint64_t a = 10UL << 32;
  SplittableUint64 proc(a);
  SplittableUint64 small(10UL, 0);
  
  std::cout << proc.get_h() << '\n' 
            << proc.get_l() << '\n'
            << proc.get_a() << '\n';
            
  std::cout << small.get_h() << '\n' 
            << small.get_l() << '\n'
            << small.get_a() << '\n';

            
  char c = proc == small ? 'y' : 'n';
  std::cout << '\n' << c;
  
}