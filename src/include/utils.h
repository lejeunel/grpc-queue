#ifndef UTILS_H_
#define UTILS_H_
#include <ctime>
#include <iostream>

namespace Utils {

std::tm datetime_now() {
  std::time_t t = std::time(0); // get time now
  std::tm *now = std::localtime(&t);
  return *now;
}

} // namespace Utils

#endif // UTILS_H_
