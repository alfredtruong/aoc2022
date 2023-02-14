#include "utils.hpp"
#include <fstream>
#include <sstream>

std::vector<std::vector<std::string>> read_csv(const std::string filepath,const char delimiter,bool verbose)
{
  std::fstream f;
  std::string line;
  std::vector<std::vector<std::string>> out;
  int lines_read = 0;

  // open file
  f.open(filepath,std::ios::in);

  // read line
  while (std::getline(f,line))
  {
    if (verbose)
    {
      lines_read++; // increment line counter
      std::cout << "[" << lines_read << "]\t";
    }

    // parse line
    std::string word;
    std::vector<std::string> words;
    std::stringstream ss(line);
    while (std::getline(ss,word,delimiter))
    {
      if (verbose)
        std::cout << word << ", ";

      words.push_back(word);
    }

    // save line
    out.push_back(words);

    if (verbose)
      std::cout << std::endl;
  }

  // close file
  f.close();

  return out;
}
