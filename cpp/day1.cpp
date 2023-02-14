#include "utils/utils.hpp"
#include "day1.hpp"
#include <iostream>
#include <map>
#include <algorithm>

namespace day1 {

// build per elf total calories
std::map<int,int> build_elf_map(std::string filename)
{
  std::vector<std::vector<std::string>> data = read_csv(filename,'\n',false);

  // compute totals for each elf
  int elf_id = 0;
  int elf_total_calories = 0;
  std::map<int,int> elf_map; // store results here

  for (int i=0;i<data.size();i++)
  {
    //std::cout << data[i].size() << std::endl;

    // accrue total for current elf
    if (data[i].size()!=0)
    {
      elf_total_calories += std::stoi(data[i][0]);
    }

    // save down results on line break OR if eof
    if (data[i].size()==0 || i == data.size() - 1)
    {
      // record current elf total
      elf_map[elf_id] = elf_total_calories; // total calories carried by elf elf_id

      // reset for next elf
      elf_id++;
      elf_total_calories = 0;
    }
  }

  // return map
  return elf_map;
}

void part_1_most_calories(std::string blurb,std::string filename)
{
  std::cout << blurb << std::endl;

  // build per elf total calories
  std::map<int,int> elf_map = build_elf_map(filename);

  // grab greatest
  int greatest_elf_id = -1;
  int greatest_elf_total_calories = -1;
  for (auto kv : elf_map)
  {
    std::cout << kv.first << " : " << kv.second << std::endl;
    if (kv.second > greatest_elf_total_calories)
    {
      greatest_elf_total_calories = kv.second;
      greatest_elf_id = kv.first;
    }
  }

  // return max total
  std::cout << "heaviest" << std::endl;
  std::cout << "- id : " << greatest_elf_id << std::endl;
  std::cout << "- total : " << greatest_elf_total_calories << std::endl;
  std::cout << std::endl;
}

void part_2_sum_top_3(std::string blurb,std::string filename,bool verbose = false)
{
  std::cout << blurb << std::endl;

  // build per elf total calories
  std::map<int,int> elf_map = build_elf_map(filename);

  // sort map
  std::vector<std::pair<int,int>> elf_vector; // sort with vector trick
  std::copy(elf_map.begin(),elf_map.end(),std::back_insert_iterator<std::vector<std::pair<int,int>>>(elf_vector));
  std::sort(elf_vector.begin(),elf_vector.end(),[](auto x,auto y){return x.second>y.second;});

  // show top 3
  int weight_id=0;
  int cum_weight_top_3=0;
  for (auto it = elf_vector.begin();it < elf_vector.begin()+3;it++)
  {
    if (verbose)
    {
      std::cout << "weight id : " << weight_id << std::endl;
      std::cout << "- id : " << it->first << std::endl;
      std::cout << "- total : " << it->second << std::endl;
      std::cout << std::endl;
      weight_id++;
    }

    cum_weight_top_3 += it->second;
  }

  std::cout << "total top 3 weight : " << cum_weight_top_3;
}

}

void day1_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day1::part_1_most_calories("test data","../input/day01_0.txt");
  day1::part_1_most_calories("question data","../input/day01_1.txt");
}

void day1_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day1::part_2_sum_top_3("test data","../input/day01_0.txt");
  day1::part_2_sum_top_3("question data","../input/day01_1.txt");
}
