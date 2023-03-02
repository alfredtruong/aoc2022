#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream> // std::cout, std::endl
#include <sstream> // std::stringstream

#define OUT(a) std::cout << __FUNCTION__ << ": " << a << std::endl << std::endl;

inline std::istream& str_to_ss(std::string str)
{
  static std::stringstream ss;
  return ss = std::stringstream(str);
}

#endif // UTILS_HPP
