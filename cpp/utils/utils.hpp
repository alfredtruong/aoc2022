#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <deque>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>

namespace utils
{

template <typename T>
std::vector<T> split_string(const std::string str,const char delimiter,bool verbose = false)
{
  //std::cout << __func__ << std::endl;
  //std::cout << s << std::endl;
  if (verbose) std::cout << "[" << __func__ << "]" << str << "|" << delimiter << "|" << verbose << std::endl;
  std::stringstream ss(str);
  std::vector<T> vec_words; // container for all parsed words
  std::string word; // temp container for single parsed word
  T converted;
  while(std::getline(ss,word,delimiter))
  {
    if (verbose) std::cout << "[" << __func__ << "], [word]" << word;

    // use stringstream to convert type
    std::stringstream ssline;
    ssline << word;
    ssline >> converted;

    if (verbose) std::cout << ", [converted]" << converted << "|" << std::endl;
    // save it
    vec_words.push_back(converted);
  }
  //if (verbose) std::cout << std::endl;
  return vec_words;
}

template <>
std::vector<std::string> split_string(const std::string str,const char delimiter,bool verbose);

/*
template <> //inline, need inline if declaring specialization in hpp, dont need inline if moving specialization into cpp file
std::vector<std::string> parse_line<std::string>(const std::string line,const char delimiter,bool verbose);
*/
template <typename T>
std::vector<std::vector<T>> parse_file(const std::string filepath,const char delimiter,bool verbose = false)
{
  // open file
  std::fstream f;
  f.open(filepath,std::ios::in);

  // read line
  std::vector<std::vector<T>> vec_lines;
  std::string line;
  int lines_read = 0;
  while (std::getline(f,line))
  {
    if (verbose)
    {
      std::cout << "[" << lines_read << "]\t";
    }

    std::vector<T> words = split_string<T>(line,delimiter,verbose); // parse line
    vec_lines.push_back(words); // save line

    if (verbose)
    {
      std::cout << std::endl;
      lines_read++; // increment line counter
    }
  }

  // close file
  f.close();

  return vec_lines;
}

template<typename T>
void display_deque(std::deque<T> dq,std::string blurb = "",std::string delimiter = "|")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << dq.size() << ", items = " << delimiter;
  for (auto x:dq) std::cout << x << delimiter;
  std::cout << std::endl;
}

template<typename T>
void display_vec(std::vector<T> v,std::string blurb = "",std::string delimiter = "|")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << v.size() << ", items = " << delimiter;
  for (auto x:v) std::cout << x << delimiter;
  std::cout << std::endl;
}

template<typename T>
void display_vecvec(std::vector<std::vector<T>> vv,std::string blurb = "",std::string delimiter = "|")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << vv.size() << ", items = " << std::endl;
  for (auto v : vv)
  {
    for (auto x : v) std::cout << x << delimiter;
    std::cout << std::endl;
  }
}

template<typename T>
void display_set(std::set<T> s,std::string blurb = "",std::string delimiter = "|")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << s.size() << ", items = ";
  for(auto x:s) std::cout << x << delimiter;
  std::cout << std::endl;
}

template<typename T,typename U>
void display_map(std::map<T,U> m,std::string blurb = "")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << m.size() << std::endl;
  for(auto kv:m) std::cout << kv.first << " : " << kv.second << std::endl;
  std::cout << std::endl;
}

template<typename T,typename U>
void display_umap(std::unordered_map<T,U> m,std::string blurb = "")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << m.size() << std::endl;
  for(auto kv:m) std::cout << kv.first << " : " << kv.second << std::endl;
  std::cout << std::endl;
}

template<typename T,typename U>
void display_mapvec(std::map<T,std::vector<U>> m,std::string blurb = "")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << m.size() << std::endl;
  for(auto kv:m) display_vec<U>(kv.second,kv.first);
  std::cout << std::endl;
}

template<typename T,typename U>
void display_umapvec(std::unordered_map<T,U> m,std::string blurb = "")
{
  if (blurb=="") blurb = __func__;
  std::cout << "[" << blurb << "] size = " << m.size() << std::endl;
  for(auto kv:m) display_vec<U>(kv.second,kv.first);
  std::cout << std::endl;
}

int char_to_int(char c);

#endif // __UTILS_HPP

}
