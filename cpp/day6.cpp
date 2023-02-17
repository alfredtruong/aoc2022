#include "utils/utils.hpp"
#include "day6.hpp"

namespace day6 {

packet::packet(std::string filepath,int signal_size)
{
  m_signal_size = signal_size;
  read_packet(filepath);
  identify_start_of_packet_marker(false,false);
}

packet::~packet() {}

void packet::read_packet(std::string filepath)
{
  std::fstream f;
  f.open(filepath,std::ios::in); // read f in readonly mode
  std::getline(f,m_packet); // read line into m_packet
  f.close();


  m_idx_start = 0;
  m_idx_end = -1;
  m_start_of_packet_marker = 0;
  m_start_of_packet_marker_found = false;
}

void packet::move_end_pointer(bool verbose)
{

  // add next char
  m_idx_end++; // move end pointer
  char add_char = m_packet[m_idx_end]; // identify next char


  // update dico with next char
  if (m_signal_dico.find(add_char)==m_signal_dico.end())
    m_signal_dico[add_char] = 1; // add it if it doesnt exist
  else
    m_signal_dico[add_char]++; // increment count if it already exists

  if (verbose)
  {
    std::cout << __func__ << " start/end = " << m_idx_start << "/" << m_idx_end << ", add_char = " << add_char << ", ";
    show_signal();
  }
}

void packet::move_start_pointer(bool verbose)
{
  // 01234 // not ok
  // 45678 // not ok

  // should rear pointer or not
  if (m_idx_end-m_idx_start==m_signal_size)
  {
    char remove_char = m_packet[m_idx_start]; // identify char to remove

    // need to shorten
    if (m_signal_dico[remove_char]==1)
      m_signal_dico.erase(remove_char); // only 1 left, remove it from dico
    else
      m_signal_dico[remove_char]--; // more than 1 left, decrement count

    m_idx_start++; // increment rear pointer

    if (verbose)
    {
      std::cout << __func__ << " start/end = " << m_idx_start << "/" << m_idx_end << ", remove_char = " << remove_char << ", ";
      show_signal();
    }
  }
}

void packet::is_start_marker_found()
{
  if ((m_idx_end-m_idx_start==m_signal_size-1) && (m_signal_dico.size()==m_signal_size))
    m_start_of_packet_marker_found = true;
}

void packet::consider_next_char(bool verbose,bool debug)
{
  move_end_pointer(verbose);   // consume next char
  move_start_pointer(verbose); // only if needed
  if (verbose) utils::display_umap(m_signal_dico);
  is_start_marker_found();  // check if start marker found
  if (debug)
  {
    std::string x;
    std::cin >> x;
  }
}

void packet::identify_start_of_packet_marker(bool verbose,bool debug)
{
  while (!m_start_of_packet_marker_found)
  {
    consider_next_char(verbose,debug);
    if (m_start_of_packet_marker_found)
    {
      m_idx_end++;
      m_start_of_packet_marker = m_idx_end;
    }
  }

  std::cout << "start marker = " << m_start_of_packet_marker << std::endl;
  show_signal();
  std::cout << std::endl;
}

void packet::show_signal()
{
  std::cout << "start signal = ";
  for (int i=m_idx_start;i<m_idx_end;i++) std::cout << m_packet[i];
  std::cout << std::endl;
}


void part_1_start_of_packer_marker(std::string blurb,std::string filepath)
{
  packet p(filepath,4);
}

void part_2_start_of_packer_marker(std::string blurb,std::string filepath)
{
  packet p(filepath,14);
}

}

void day6_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day6::part_1_start_of_packer_marker("test data","../input/day06_0a.txt");
  day6::part_1_start_of_packer_marker("test data","../input/day06_0b.txt");
  day6::part_1_start_of_packer_marker("test data","../input/day06_0c.txt");
  day6::part_1_start_of_packer_marker("test data","../input/day06_0d.txt");
  day6::part_1_start_of_packer_marker("test data","../input/day06_0e.txt");
  day6::part_1_start_of_packer_marker("actual data","../input/day06_1.txt");
}

void day6_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day6::part_2_start_of_packer_marker("test data","../input/day06_0a.txt");
  day6::part_2_start_of_packer_marker("test data","../input/day06_0b.txt");
  day6::part_2_start_of_packer_marker("test data","../input/day06_0c.txt");
  day6::part_2_start_of_packer_marker("test data","../input/day06_0d.txt");
  day6::part_2_start_of_packer_marker("test data","../input/day06_0e.txt");
  day6::part_2_start_of_packer_marker("actual data","../input/day06_1.txt");
}
