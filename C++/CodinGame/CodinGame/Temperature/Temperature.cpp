#include <algorithm>
#include <iostream>
#include <vector>

static bool is_lower(int a, int b) {
  return a < b;
}

static int closest(std::vector<int> v, int value_to_compare_to) {
  std::sort(v.begin(), v.end(), is_lower);

  auto iter = std::lower_bound(v.begin(), v.end(), value_to_compare_to);
  /* std::lower_bound doesn't check for negative numbers
   * so if it didn't find anything the value is negative,
   * therefore we just need the highest one.
   */

  if (iter == v.end()) { return *(std::max_element(v.begin(), v.end(), is_lower)); }

  // Return the value of 'iter' since it's a pointer to a position in the vector
  return *iter;
}

int main() {

  std::vector<int> temperatures_to_analyse;

  int number_of_temperatures_to_analyse;
  std::cin >> number_of_temperatures_to_analyse;
  std::cin.ignore();

  for (int i = 0; i < number_of_temperatures_to_analyse; i++) {
    int temperature = 0;
    std::cin >> temperature;
    std::cin.ignore();

    if (temperature == 0) { // If the temp is 0 we know we can print 0
      std::cout << 0 << std::endl;
      std::exit(EXIT_SUCCESS);
    } else {
      temperatures_to_analyse.push_back(temperature);
    }
  }

  /* DEBUG:
   for (auto& val:temperatures_to_analyse) std::cerr << val << ", ";
   std::cerr << std::endl;
   */

  if (not temperatures_to_analyse.empty()) {
    std::cout << closest(temperatures_to_analyse, 0);
  } else {
    std::cout << "0";
  }
  std::cout << std::endl;
}
