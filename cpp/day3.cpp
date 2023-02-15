#include "utils/utils.hpp"
#include "day3.hpp"
#include <set>
#include <algorithm>

namespace day3 {

//      prio
// a -> 1
// A -> 27
int char_to_prio(char c)
{
  //      ascii
  // A -> 65-90
  // a -> 97-122
  int prio = (int)c;

  if (prio > 96)
    return prio-96; // lowercase
  else
    return prio-64+26; // uppercase
}

//vJrwpWtwJgWr
//hcsFMMfFFhFp
char identify_double_packed_item(std::string packed_items)
{
  std::set<char> compartment_items;
  int num_items = packed_items.length()/2;

  //std::cout << packed_items.length() << " " << num_items << std::endl;;

  // populate bag part1
  for (int i=0;i<num_items;i++)
  {
    compartment_items.insert(packed_items[i]);
    //std::cout << compartment_items.size() << std::endl;
  }

  // find duplicated item from remaining items
  int i=num_items;
  while(compartment_items.find(packed_items[i])==compartment_items.end())
  {
    i++;
  }
  char duplicated_item = packed_items[i];
  // duplicated item found
  //std::cout << duplicated_item << " : " << char_to_prio(duplicated_item) << " : " << num_items << " : " << packed_items << std::endl;

  // duplicated item found
  return duplicated_item;
}

void part_1_sum_packing_priorities(std::string blurb,std::string filepath)
{
  std::vector<std::vector<std::string>> data = utils::parse_file<std::string>(filepath,' ',false);

  int total_prio = 0;
  int packed_items = 0;
  for (auto x : data)
  {
    std::string str = x[0];
    char double_packed_item = identify_double_packed_item(str);
    int prio = char_to_prio(double_packed_item);
    total_prio += prio;
    packed_items++;
  }

  std::cout << "packed_items = " << packed_items << std::endl;
  std::cout << "total_prio = " << total_prio << std::endl;
}

// find item that appears in all 3 rucksacks
char identify_elf_group_badge(std::string e1,std::string e2,std::string e3,bool verbose = false)
{
  std::set<char> s1;
  std::set<char> s2;
  std::set<char> s3;

  // populate s1,s2 and s3
  for(auto c:e1) s1.insert(c);
  for(auto c:e2) s2.insert(c);
  for(auto c:e3) s3.insert(c);

  if (verbose) utils::display_set(s1);
  if (verbose) utils::display_set(s2);
  if (verbose) utils::display_set(s3);

  // intersect e1 and e2
  std::set<char> intersect12;
  std::set_intersection(s1.begin(),s1.end(),
                        s2.begin(),s2.end(),
                        std::inserter(intersect12,intersect12.begin()));
  if (verbose) utils::display_set(intersect12);

  // intersect e2 and e3
  std::set<char> intersect23;
  std::set_intersection(s2.begin(),s2.end(),
                        s3.begin(),s3.end(),
                        std::inserter(intersect23,intersect23.begin()));
  if (verbose) utils::display_set(intersect23);

  // intersect e12 and e23
  std::set<char> intersect123;
  std::set_intersection(intersect12.begin(),intersect12.end(),
                        intersect23.begin(),intersect23.end(),
                        std::inserter(intersect123,intersect123.begin()));
  if (verbose) utils::display_set(intersect123);

  if (intersect123.size() == 1)
    return *(intersect123.begin());
  else
    exit(1);
}

void part_2_sum_group_badge_priorities(std::string blurb,std::string filepath)
{
  std::vector<std::vector<std::string>> data = utils::parse_file<std::string>(filepath,' ',false);

  int i = 0;
  int group_counter = 0;
  int total_group_prio = 0;
  while (i < data.size())
  {
    char group_badge = identify_elf_group_badge(
      data[i][0],
      data[i+1][0],
      data[i+2][0]
    );
    i+=3;
    group_counter++;
    int group_prio = char_to_prio(group_badge);
    total_group_prio += group_prio;
    std::cout << group_counter << " : " << group_badge << std::endl;

  }

  std::cout << "groups = " << group_counter << std::endl;
  std::cout << "total_group_prio = " << total_group_prio << std::endl;
}

}

void day3_part1()
{
  std::cout << __func__ << std::endl << std::endl;

  /* //validate prio
  std::cout << day3::char_to_prio('a') << std::endl;
  std::cout << day3::char_to_prio('z') << std::endl;
  std::cout << day3::char_to_prio('A') << std::endl;
  std::cout << day3::char_to_prio('Z') << std::endl;
  */

  /* // validate identify_double_packed_item
  day3::identify_double_packed_item("vJrwpWtwJgWrhcsFMMfFFhFp");
  day3::identify_double_packed_item("jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL");
  day3::identify_double_packed_item("PmmdzqPrVvPwwTWBwg");
  day3::identify_double_packed_item("wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn");
  day3::identify_double_packed_item("ttgJtRGJQctTZtZT");
  day3::identify_double_packed_item("CrZsJsPPZsGzwwsLwLmpwMDw");
  */

  day3::part_1_sum_packing_priorities("test data","../input/day03_0.txt");
  day3::part_1_sum_packing_priorities("test data","../input/day03_1.txt");
}

void day3_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  /*
  char group_badge = day3::identify_elf_group_badge(
    "vJrwpWtwJgWrhcsFMMfFFhFp",
    "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
    "PmmdzqPrVvPwwTWBwg"
  );
  std::cout << group_badge << std::endl;
  */
  day3::part_2_sum_group_badge_priorities("test data","../input/day03_0.txt");
  day3::part_2_sum_group_badge_priorities("test data","../input/day03_1.txt");
}
