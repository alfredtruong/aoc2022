#include "utils/utils.hpp"
#include "day4.hpp"
#include <string>

namespace day4 {

int elf_jobs_min(std::string elf_jobs)
{
  std::string s(1,elf_jobs[0]);
  return std::stoi(s);
}

int elf_jobs_max(std::string elf_jobs)
{
  std::string s(1,elf_jobs[elf_jobs.length()-1]);
  return std::stoi(s);
}

void elf_jobs_print(std::string elf_jobs)
{
    std::cout << elf_jobs << " : " << elf_jobs_min(elf_jobs) << " : " << elf_jobs_max(elf_jobs) << std::endl;
}

bool do_elf_jobs_fully_overlap(std::string elf1_jobs,std::string elf2_jobs)
{
  elf_jobs_print(elf1_jobs);
  elf_jobs_print(elf2_jobs);
  return false;
}

void part_1_fully_overlapping_count(std::string blurb,std::string filename)
{

  std::vector<std::vector<std::string>> data = read_csv(filename,',',false);

  int fully_overlapping_count = 0;
  for (auto x : data)
  {
    std::string elf1_jobs = x[0];
    std::string elf2_jobs = x[1];
    bool does_overlap = do_elf_jobs_fully_overlap(elf1_jobs,elf2_jobs);

    if (does_overlap)
      fully_overlapping_count++;
  }

  std::cout << "fully_overlapping_count = " << fully_overlapping_count << std::endl;
}

}

void day4_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day4::part_1_fully_overlapping_count("test data","../input/day04_0.txt");
  day4::part_1_fully_overlapping_count("test data","../input/day04_1.txt");
}

void day4_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day4::part_1_fully_overlapping_count("test data","../input/day04_0.txt");
  day4::part_1_fully_overlapping_count("test data","../input/day04_1.txt");
}
