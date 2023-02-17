#ifndef __DAY7_HPP
#define __DAY7_HPP

namespace day7
{

typedef std::string dirname; // name of a directory
typedef std::string objname; // name of an object, be it file or directory

class df
{
private:
  // data structures to map file structure
  std::map<dirname,std::vector<objname>> m_dirContentsMap; // what does each directory contain
  std::map<objname,int> m_objSizeMap; // map to contain size of objects

  // variables for directory mapping
  std::vector<std::string> m_cwd; // from root to cwd of interest

public:
  df(std::string filepath,bool verbose=false);
  ~df();

  void inspect_containers();

  bool is_obj_dir(std::string obj);
  int objsize(std::string obj);
  void populate_directory_contents_map(std::string dname,bool verbose=false);
  bool is_line_command(const std::string line,bool verbose=false);
  void parse_terminal_output(std::string filepath,bool verbose=false);

  void parse_command(const std::string line,std::string &cmd,std::string &args,bool verbose=false);
  void cd_update_cwd(std::string cmd,std::string args);
  void ls_parse_output(std::string line,bool verbose=false);
  void compute_dirsizes(bool verbose=false);
  int sum_dirsizes_less_than_x(int max_size);
  std::string cwd_to_string(const std::vector<std::string> vec,const std::string subdir="");

};

}

void day7_part1();
void day7_part2();

#endif // __DAY7_HPP
