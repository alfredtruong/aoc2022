#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <set>

std::vector<std::vector<std::string>> read_csv(const std::string filepath,const char delimiter,bool verbose = false);

template<typename T>
void show_vector(std::vector<T> v)
{
  for (auto x:v) {
    std::cout << x;
    std::cout << ", ";
  }
  std::cout << std::endl;
}

template<typename T>
void show_set(std::set<T> s)
{

  std::cout << s.size() << std::endl;
  for(auto c:s) std::cout << c;
  std::cout << std::endl;
}

int char_to_int(char c);

#endif // __UTILS_HPP
