#include "utils/utils.hpp"
#include "day4.hpp"
#include <string>

namespace day4 {

void elf_jobs_print(std::string elf_jobs)
{
  std::vector<int> elf_jobs_parsed = utils::parse_line<int>(elf_jobs,'-',false);
  std::cout << elf_jobs << " : " << elf_jobs_parsed[0] << " : " << elf_jobs_parsed[1] << std::endl;
}

bool do_elf_jobs_fully_overlap(std::string elf1_jobs,std::string elf2_jobs)
{
  //std::cout << __func__ << std::endl;
  //elf_jobs_print(elf1_jobs);
  //elf_jobs_print(elf2_jobs);

  std::vector<int> elf1_jobs_parsed = utils::parse_line<int>(elf1_jobs,'-',false);
  std::vector<int> elf2_jobs_parsed = utils::parse_line<int>(elf2_jobs,'-',false);

  if (
      ((elf1_jobs_parsed[0] <= elf2_jobs_parsed[0]) && (elf1_jobs_parsed[1] >= elf2_jobs_parsed[1])) || // elf1_jobs encapsulate elf2_jobs
      ((elf2_jobs_parsed[0] <= elf1_jobs_parsed[0]) && (elf2_jobs_parsed[1] >= elf1_jobs_parsed[1]))    // elf2_jobs encapsulate elf1_jobs
  )
  {
    return true;
  }
  else
  {
    return false;
  }
}
void part_1_fully_overlapping_count(std::string blurb,std::string filename,bool verbose = false)
{
  std::vector<std::vector<std::string>> data = utils::parse_file<std::string>(filename,',');

  //std::cout << __func__ << " : " << data.size() << std::endl;
  int fully_overlapping_count = 0;
  for (auto x : data)
  {
    // std::cout << "here : " << x.size() << std::endl;
    std::string elf1_jobs = x[0];
    std::string elf2_jobs = x[1];
    // std::cout << elf1_jobs << std::endl;
    // std::cout << elf2_jobs << std::endl;

    bool is_fully_overlapping = do_elf_jobs_fully_overlap(elf1_jobs,elf2_jobs);

    if (is_fully_overlapping)
    {
      fully_overlapping_count++;
      if (verbose)
      {
        //std::cout << __func__ << std::endl;
        //elf_jobs_print(elf1_jobs);
        //elf_jobs_print(elf2_jobs);
        std::cout << "[" << fully_overlapping_count << "] " << elf1_jobs << ", " << elf2_jobs << std::endl;
      }
    }
  }

  // report fully overlapping count
  std::cout << "fully_overlapping_count = " << fully_overlapping_count << std::endl;
}

bool do_elf_jobs_partially_overlap(std::string elf1_jobs,std::string elf2_jobs)
{
  //std::cout << __func__ << std::endl;
  //elf_jobs_print(elf1_jobs);
  //elf_jobs_print(elf2_jobs);

  std::vector<int> elf1_jobs_parsed = utils::parse_line<int>(elf1_jobs,'-',false);
  std::vector<int> elf2_jobs_parsed = utils::parse_line<int>(elf2_jobs,'-',false);

  if (
      ((elf1_jobs_parsed[1] >= elf2_jobs_parsed[0]) && (elf1_jobs_parsed[0] <= elf2_jobs_parsed[1])) // elf1_jobs overlaps elf2_jobs
  )
  {
    return true;
  }
  else
  {
    return false;
  }
}

void part_2_partially_overlapping_count(std::string blurb,std::string filename,bool verbose = false)
{
  std::vector<std::vector<std::string>> data = utils::parse_file<std::string>(filename,',');

  //std::cout << __func__ << " : " << data.size() << std::endl;
  int partially_overlapping_count = 0;
  for (auto x : data)
  {
    // std::cout << "here : " << x.size() << std::endl;
    std::string elf1_jobs = x[0];
    std::string elf2_jobs = x[1];
    // std::cout << elf1_jobs << std::endl;
    // std::cout << elf2_jobs << std::endl;

    bool is_partially_overlapping = do_elf_jobs_partially_overlap(elf1_jobs,elf2_jobs);

    if (is_partially_overlapping)
    {
      partially_overlapping_count++;
      if (verbose)
      {
        //std::cout << __func__ << std::endl;
        //elf_jobs_print(elf1_jobs);
        //elf_jobs_print(elf2_jobs);
        std::cout << "[" << partially_overlapping_count << "] " << elf1_jobs << ", " << elf2_jobs << std::endl;
      }
    }
  }

  // report partially overlapping count
  std::cout << "partially_overlapping_count = " << partially_overlapping_count << std::endl;
}

}

void day4_part1()
{
  //std::cout << __func__ << std::endl << std::endl;
  day4::part_1_fully_overlapping_count("test data","../input/day04_0.txt",true);
  day4::part_1_fully_overlapping_count("test data","../input/day04_1.txt",true);
}

void day4_part2()
{
  //std::cout << __func__ << std::endl << std::endl;
  day4::part_2_partially_overlapping_count("test data","../input/day04_0.txt",true);
  day4::part_2_partially_overlapping_count("test data","../input/day04_1.txt",true);
}
