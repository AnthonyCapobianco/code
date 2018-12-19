#pragma once

#include "temperature.hpp"
#include <string>

class TemperatureConverter : Temperature {
private:
  Temperature m_temperature;
  double m_kelvin;
  double m_celsius;
  double m_fahrenheit;
  
private:
  Unit c_to_unit(const char* unit) const noexcept(false) {
    switch (toupper(unit[0])) {
      default: case 'C':
        return celsius;
      case 'F':
        return fahrenheit;
      case 'K':
        return kelvin;
    }
  }
  
  double celsius_to_fahrenheit(double temp_c) const noexcept(true) {
    return (temp_c * 1.8) + 32;
  }
  
  double fahrenheit_to_celsius(double temp_f) const noexcept(true) {
    return (temp_f - 32) / 1.8;
  }
  
  double celsius_to_kelvin(double temp_c) const noexcept(true) {
    return temp_c + 273.15;
  }
  
  double kelvin_to_celsius(double temp_k) const noexcept(true) {
    return temp_k - 273.15;
  }
  
  void set_temperatures(Temperature t) noexcept(false) {
    if (t.get_unit() == celsius) {
      m_celsius = t.get_temperature();
      m_fahrenheit = celsius_to_fahrenheit(m_celsius);
      m_kelvin = celsius_to_kelvin(m_celsius);
    } 
    
    if (t.get_unit() == fahrenheit) {
      m_fahrenheit = t.get_temperature();
      m_celsius = fahrenheit_to_celsius(m_fahrenheit);
      m_kelvin = celsius_to_kelvin(m_celsius);
    } 
    
    if (t.get_unit() == kelvin) {
      m_kelvin = t.get_temperature();
      m_celsius = kelvin_to_celsius(m_kelvin);
      m_fahrenheit = celsius_to_fahrenheit(m_celsius);
    }
  }

public:
  TemperatureConverter(const char* temp, const char* unit = "C") noexcept(false) 
    : m_temperature(Temperature(atof(temp), c_to_unit(unit))) {
    set_temperatures(m_temperature);
  }

  double get_celsius() const noexcept(true) {
    return m_celsius;
  }
  
  double get_fahrenheit() const noexcept(true) {
    return m_fahrenheit;
  }
  
  double get_kelvin() const noexcept(true) {
    return m_kelvin;
  }
};
