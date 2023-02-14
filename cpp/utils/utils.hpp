#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <vector>
#include <string>
#include <iostream>

std::vector<std::vector<std::string>> read_csv(const std::string filepath,const char delimiter,bool verbose = false);

template<typename T>
void show_vec(std::vector<T> vec)
{
  for (auto x:vec) {
    std::cout << x;
    std::cout << ", ";
  }
  std::cout << std::endl;
}

#endif // __UTILS_HPP
