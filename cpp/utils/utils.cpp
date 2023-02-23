#include "utils.hpp"

namespace utils
{

template <>
std::vector<std::string> split_string(const std::string str,const char delimiter,bool verbose)
{
  //std::cout << __func__ << std::endl;
  //std::cout << s << std::endl;
  if (verbose) std::cout << "[" << __func__ << "]" << str << "|" << delimiter << "|" << verbose << std::endl;
  std::stringstream ss(str);
  std::vector<std::string> vec_words; // container for all parsed words
  std::string word; // temp container for single parsed word
  while(std::getline(ss,word,delimiter))
  {
    if (verbose) std::cout << "[" << __func__ << "], [word]" << word;
    // save it
    vec_words.push_back(word);
  }
  //if (verbose) std::cout << std::endl;
  return vec_words;
}


/*
template <>
std::vector<std::string> parse_line<std::string>(const std::string line,const char delimiter,bool verbose)
{
  std::cout << __func__ << " = string" << std::endl;
  std::cout << line << std::endl;

  std::stringstream ss(line);
  std::vector<std::string> vec_words; // container for all parsed words
  std::string word; // temp container for single parsed word
  while(std::getline(ss,word,'-'))
  {
    if (verbose)
    {
      std::cout << word << std::endl;
      vec_words.push_back(word);
    }
  }
  return vec_words;
}
*/

int char_to_int(char c)
{
  return (int)c - 48;
}

}
