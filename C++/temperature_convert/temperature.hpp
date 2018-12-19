#pragma once

#define DO_NOTHING() 0

class Temperature {
protected:
  enum Unit {
    fahrenheit = 'F'
  , celsius = 'C'
  , kelvin = 'K'
  };

private:
  double m_temperature;
  Unit m_unit;
  
public:
  Temperature() noexcept(true) {
    DO_NOTHING();
  }
  
  Temperature(double temperature, Unit unit) noexcept(true)
    : m_temperature(temperature)
    , m_unit(unit)
  {
  }
  
  double get_temperature() const noexcept(true) {
    return m_temperature;
  }
  
  Unit get_unit() const noexcept(true) {
    return m_unit;
  }
};

#undef DO_NOTHING