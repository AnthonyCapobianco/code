#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace Game {



class Game {
private:
  std::pair<int, int> _position;
  std::pair<int, int> _light_position;
  std::pair<int, int> _difference;

  void SetLightPosition() {
    std::cin >> this->_light_position.first >> this->_light_position.second;
  }

  void SetPlayerPosition() {
    std::cin >> this->_position.first >> this->_position.second;
    std::cin.ignore();
  }

  void SetPositionDifference() {

    this->_difference.first = this->_light_position.first - this->_position.first;
    this->_difference.second = this->_light_position.second - this->_position.second;
  }

public:
  Game() {
    this->SetLightPosition();
    this->SetPlayerPosition();
  }

  void GoToObjective() {
    this->SetPositionDifference();

    while (this->_difference != std::make_pair(0, 0)) {

      if (this->_difference.second > 0) {
        std::cout << "S";
        this->_difference.second--;
      } else if (this->_difference.second < 0) {
        std::cout << "N";
        this->_difference.second++;
      }

      if (this->_difference.first > 0) {
        std::cout << "E";
        this->_difference.first--;
      } else if (this->_difference.first < 0) {
        std::cout << "W";
        this->_difference.first++;
      }

      std::cout << std::endl;
    }
  }
};

}


int main() {
  Game::Game thor;

  while (true) {
    int remaining_turns;
    std::cin >> remaining_turns;
    std::cin.ignore();

    thor.GoToObjective();
  }
}
