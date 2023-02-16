#ifndef __DAY6_HPP
#define __DAY6_HPP

#include <fstream>

namespace day6
{

class packet
{
private:
  int m_signal_size;
  std::string m_packet;
  std::unordered_map<char,int> m_signal_dico;
  int m_idx_start;
  int m_idx_end;
  int m_start_of_packet_marker;
  bool m_start_of_packet_marker_found;

public:
  packet(std::string filepath,int signal_size);
  ~packet();

  void read_packet(std::string filepath);
  void move_end_pointer(bool verbose);
  void move_start_pointer(bool verbose);
  void is_start_marker_found();
  void consider_next_char(bool verbose,bool debug);
  void identify_start_of_packet_marker(bool verbose,bool debug);
  void show_signal();
};

}

void day6_part1();
void day6_part2();

#endif // __DAY6_HPP
