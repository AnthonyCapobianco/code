#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int correct_vertical_speed(int vertical_speed) noexcept(true) {
  if (vertical_speed <= -40) {
    return 4;
  } else if (vertical_speed <= -30) {
    return 3;
  } else if (vertical_speed <= -20) {
    return 2;
  } else if (vertical_speed <= -10) {
    return 1;
  } 
  return 0;
}

int correct_heading(int horizontal_speed, int angle_of_rotation) noexcept(true) {
  // TODO: Implement this function 乁( •_• )ㄏ 
  return 0;
}

int main() {
  int num_surface_points; // the number of points used to draw the surface of Mars.
  std::cin >> num_surface_points; 
  std::cin.ignore();
  
  for (int i = 0; i < num_surface_points; i++) {
    int surface_point_x;
    int surface_point_y;
    std::cin >> surface_point_x >> surface_point_y; 
    std::cin.ignore();
  }

  while (true) {
    int pos_x;
    int pos_y;
    int horizontal_speed;
    int vertical_speed;
    int remaining_fuel;
    int angle_of_rotation;
    int thrust; 
    
    std::cin >> pos_x 
      >> pos_y 
      >> horizontal_speed 
      >> vertical_speed 
      >> remaining_fuel 
      >> angle_of_rotation 
      >> thrust;
    
    std::cin.ignore();
    
    int thrust_correction = correct_vertical_speed(vertical_speed);
    //int heading_correction = correct_heading(horizontal_speed, angle_of_rotation);
    
    std::cout << -angle_of_rotation << ' ' 
      << thrust_correction << std::endl;

  }
}