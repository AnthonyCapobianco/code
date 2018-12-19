#pragma once

#include <ctime>
#include <array>
#include <iostream>

namespace vt {
namespace calendar {

enum WeekDay {
  sunday
, monday
, tuesday
, wednesday
, thursday
, friday
, saturday
};

class [[nodiscard]] Cal {
private:
  static constexpr std::array<char[4], 31> kCalView{
    " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 "
  , " 8 ", " 9 ", "10 ", "11 ", "12 ", "13 ", "14 "
  , "15 ", "16 ", "17 ", "18 ", "19 ", "20 ", "21 "
  , "22 ", "23 ", "24 ", "25 ", "26 ", "27 ", "28 "
  , "29 ", "30 ", "31 "
  };
  
  int m_day;
  int m_month;
  int m_year;
  WeekDay m_day_of_the_week;
  WeekDay m_first_day_of_month;
  int m_month_length;

public:
  Cal() noexcept(true) {
    std::time_t today{ std::time(nullptr) };
    std::tm* time_struct{ std::localtime(&today) };
    m_day = time_struct->tm_mday;
    m_month = time_struct->tm_mon;
    m_year = time_struct->tm_year;
    m_day_of_the_week = static_cast<WeekDay>(time_struct->tm_wday);

    time_struct->tm_mday = 1;
    std::mktime(time_struct);
    m_first_day_of_month = static_cast<WeekDay>(time_struct->tm_wday);

    m_month_length = days_in_month();
  }

private:
  inline bool is_leap_year() const noexcept(true) {
    return (m_year % 100 != 0 and m_year % 4 == 0) or m_year % 400 == 0;
  }

  const int days_in_month() const noexcept(true) {
    switch (m_month - 1) {
      case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
      case 2:
        return (is_leap_year()) ? 29 : 28;
      case 4: case 6: case 9: case 11:
        return 30;
    }
    return -1;
  }

public:
  inline const std::string format() const noexcept(false) {
    std::string result(1 + (m_first_day_of_month - 1) * 3, ' ');
    result.reserve(150);
    int i{ m_first_day_of_month };
    
    for (int j = 0; j < m_month_length; ++j, ++i) {
      if (j == m_day) {
        result += "\x1b[1;37;40m";
        result += kCalView.at(j);
        result += "\x1b[0;97m";
      } else {
        result += kCalView.at(j);
      }
      
      if (i % 7 == 0) {
        result += "\n ";
      }
    }
    return result;
  }

  friend std::ostream& operator<<(std::ostream& out, const Cal& cal) {
    return out << "  S  M  T  W  T  F  S\n" << cal.format();
  }
};


} // namespace calendar
} // namespace vt
