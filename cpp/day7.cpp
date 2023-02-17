#include "utils/utils.hpp"
#include "day7.hpp"

namespace day7
{

void df::inspect_containers()
{
  std::cout << std::endl;
  utils::display_mapvec(m_dirContentsMap,"m_dirContentsMap");
  utils::display_map(m_objSizeMap,"m_objSizeMap");
  std::cout << std::endl;
}

df::df(std::string filepath,bool verbose)
{
  parse_terminal_output(filepath); // start parting terminal output

  if (verbose) inspect_containers();
  compute_dirsizes();
}

df::~df()
{
  for (auto kv:m_dirContentsMap)
  {
    kv.second.clear(); // free memory
    // delete kv.second; // free memory
  }
}

bool df::is_line_command(const std::string line,bool verbose)
{
  bool res = (line[0] == '$') ? true : false;
  if (verbose) std::cout << __func__ << " line = " << line << ", is_line_command = " << res << std::endl;
  return res;
}

void df::populate_directory_contents_map(std::string dname,bool verbose)
{
  if (m_dirContentsMap.find(dname)==m_dirContentsMap.end())
  {
    if (verbose) std::cout << "[" << __func__ << "] create " << dname << std::endl;
    std::vector<std::string> vec; // how to do this better
    m_dirContentsMap[dname] = vec;
  }
}

// is object a directory or not?
bool df::is_obj_dir(std::string obj)
{
  return (m_dirContentsMap.find(obj) != m_dirContentsMap.end()) ? true : false;
}

// recursive call to compute object size
// file sizes should be populated at init
// dir sizes are computed and cached for future use, i.e. on 1st call
int df::objsize(std::string obj)
{
  if (m_objSizeMap.find(obj) != m_objSizeMap.end())
  {
    // already computed, return it
    // could be a file or a directory
    return m_objSizeMap[obj];
  }
  else
  {
    // not populated, compute it, populate m_objSizeMap and return it
    if (is_obj_dir(obj))
    {
      // must be a directory, files should be populated at init
      int dirsize = 0; // handles case of empty directory
      for (auto dirobj : m_dirContentsMap[obj])
      {
        dirsize += objsize(dirobj);
      }
      m_objSizeMap[obj] = dirsize;
      return dirsize;
    }
    else
    {
      // this shouldn't happen, file sizes should be populated at init
      std::cout << __func__ << " exit1" << std::endl;
      exit(1);
    }
  }
}

// parse file
void df::parse_terminal_output(std::string filepath,bool verbose)
{
  // open file
  std::fstream f;
  f.open(filepath,std::ios::in); // readonly

  // read line by line
  int line_number=0;
  std::string line;
  while (std::getline(f,line))
  {
    if (verbose) std::cout << "[" << line_number << "] ";
    line_number++;

    if (is_line_command(line))
    {
      if (verbose) std::cout << "[user cmd] line = '" << line << "'" << std::endl;
      if (verbose) utils::display_vector(m_cwd,"m_cwd"); // where am i

      std::string cmd = "";
      std::string args = "";
      parse_command(line,cmd,args);
      if (cmd == "cd")
      {
        if (verbose) std::cout << "[" << __func__ << "] cd" << std::endl;
        cd_update_cwd(cmd,args);
      }
      else if (cmd == "ls")
      {
        if (verbose) std::cout << "[" << __func__ << "] ls" << std::endl;
      }
      else
      {
        std::cout << __func__ << " exit1" << std::endl;
        exit(1);
      }
    }
    else
    {
      if (verbose) std::cout << "ls output = " << line << std::endl;
      ls_parse_output(line);
    }

    // debug stuff
    if (verbose) inspect_containers();
  }

  // close file
  f.close();
}

void df::parse_command(const std::string line,std::string &cmd,std::string &args,bool verbose)
{
  std::vector<std::string> parsed_line = utils::split_string<std::string>(line,' ');
  if (verbose) utils::display_vector(parsed_line,"parsed_line");
  cmd = parsed_line[1];
  if (parsed_line.size()==2)
  {
    // no args
    args = ' '; // what exactly does nullptr do?!
  }
  else
  {
    // assume there is only 1 arg for all commands
    args = parsed_line[2];
  }

  if (verbose) std::cout << "[" << __func__ << "] line = '" << line << "', cmd = '" << cmd << "', args = '" << args << "'" << std::endl;
}

void df::cd_update_cwd(std::string cmd,std::string args)
{
  if (args == "/")
  {
    // root
    m_cwd.clear(); // truncate vector and populate with root
    m_cwd.push_back(args);
    populate_directory_contents_map(cwd_to_string(m_cwd)); // know "/" exists, create it if not already created
  }
  else if (args == "..")
  {
    // up a level
    m_cwd.pop_back();
  }
  else
  {
    // go deep one level
    m_cwd.push_back(args); // append changed to directory to vector
    populate_directory_contents_map(cwd_to_string(m_cwd)); // know "{args}" exists, create it if not already created
  }
}

std::string df::cwd_to_string(const std::vector<std::string> vec,const std::string subdir)
{
  std::string s=vec[0];
  for (int i=1;i<vec.size();i++)
  {
    s+=vec[i];
    s+="/";
  }
  if (subdir!="")
  {
    s+=subdir;
    s+="/";
  }
  return s;
}

void df::ls_parse_output(std::string line,bool verbose)
{
  std::string cwd_str = cwd_to_string(m_cwd);
  std::vector<std::string> parsed_line = utils::split_string<std::string>(line,' ');

  if (verbose) std::cout << cwd_str << " ";
  if (verbose) utils::display_vector<std::string>(m_dirContentsMap[cwd_str],cwd_str);

  std::string dir_or_filesize = parsed_line[0];
  std::string objname = parsed_line[1];
  if (dir_or_filesize == "dir")
  {
    // dir
    populate_directory_contents_map(cwd_to_string(m_cwd,objname)); // make container for directory if it doesnt already exist
    m_dirContentsMap[cwd_str].push_back(cwd_to_string(m_cwd,objname));
  }
  else
  {
    // file
    int filesize = std::stoi(dir_or_filesize);
    m_objSizeMap[objname] = filesize;
    m_dirContentsMap[cwd_str].push_back(objname);
  }
}

void df::compute_dirsizes(bool verbose)
{
  for (auto kv:m_dirContentsMap)
  {
    int this_size=0;
    for (auto x:kv.second)
    {
      if (verbose) std::cout << x << std::endl;
      this_size += objsize(x); // free memory
    }
    if (verbose) std::cout << kv.first << " = " << this_size << std::endl;
    // delete kv.second; // free memory
  }
}

int df::sum_dirsizes_less_than_x(int max_size)
{
  int sum_dirsizes = 0;
  for (auto kv : m_dirContentsMap)
  {
    int dirsize = objsize(kv.first);
    if (dirsize<=max_size)
    {
      sum_dirsizes += dirsize;
      std::cout << kv.first << ", dirsize = " << dirsize << ", total = " << sum_dirsizes << ", included" << std::endl;
    }
    else
    {
      std::cout << kv.first << ", dirsize = " << dirsize << ", total = " << sum_dirsizes << ", ignore" << std::endl;
    }
  }
  return sum_dirsizes;
}

void part_1(std::string blurb,std::string filepath)
{
  std::cout << blurb << std::endl;
  df x(filepath,true);
  std::cout << std::endl;
  x.sum_dirsizes_less_than_x(100000);
}

}

void day7_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day7::part_1("test data","../input/day07_0.txt");
  day7::part_1("test data","../input/day07_1.txt");
}

void day7_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  //day7::part_1("test data","../input/day07_0.txt");
  //day7::part_1("test data","../input/day07_1.txt");
}
