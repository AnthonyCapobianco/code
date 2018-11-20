#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <clocale>

typedef std::vector<std::string> ascii_rows;

int main() {
  int length;
  std::cin >> length; std::cin.ignore();
  
  int height;
  std::cin >> height; std::cin.ignore();
  
  std::string target;
  getline(std::cin, target);
  
  ascii_rows rows;
  
  for (int i = 0; i < height; i++) {
    std::string line;
    std::getline(std::cin, line);
    
    rows.push_back(line);
  }
  
  ascii_rows output;
  std::size_t target_size = target.size();
  
  for (std::size_t i = 0; i < target_size; i++) {
    int target_start = 26;
    
    if ((target.at(i) >= 'A' and target.at(i) <= 'Z') or
      (target.at(i) >= 'a' and target.at(i) <= 'z')) {
      target_start = static_cast<int>((std::toupper(target.at(i)) - 'A'));
    }
    
    target_start *= length;
    
    try {
      if (i == 0) {
        for (auto line: rows) {
          output.push_back(line.substr(target_start, length));
        }
      } else {
        for (int j = 0; j < height; j++) {
          output.at(j) += rows.at(j).substr(target_start, length);
        }
      }
    } catch(const std::out_of_range& e) {
      std::cerr << "Target out of range" << std::endl;
    }

  }

  for (auto line: output) {
    std::cout << line << '\n';
  }
  std::cout << std::endl;
  
  //std::cerr << static_cast<int>(target - 'A') << std::endl;
}