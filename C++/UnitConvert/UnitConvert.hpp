/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <cstdint>

namespace viral {

struct Unit {
public:
  enum System : unsigned char {
    SI
  , metric = SI
  , US
  , imperial
  };
  
  template<System S> struct Measurement;
  
  template<System S> struct Length : Measurement<S> {
    int64_t in, ft, yr, mile;
  };
  
  
};

template <Unit::System S = Unit::System::metric> 
class UnitConvert {
private:
  

public:
  UnitConvert() noexcept(true) {
    
  }

};
}