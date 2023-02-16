#ifndef __DAY6_HPP
#define __DAY6_HPP

#include <unordered_map>
#include <fstream>
namespace day6
{

class packet
{
private:
  std::string m_packet;
  unordered_map<char,int> m_signal_dico;
  int m_idx_start;
  int m_idx_end;
  int m_start_of_packet_marker;
  bool m_start_of_packet_marker_found;
public:
  packet(std::string filepath)
  {
    read_packet(filepath);
    identify_start_of_packet_marker();
  }

  ~packet();

  read_packet(std::string filepath)
  {
    fstream f;
    f.open(filepath,std::ios::in); // read f in readonly mode
    std::getline(f,m_packet); // read line into m_packet
    f.close();


    m_idx_start = 0;
    m_idx_end = 0;
    m_start_of_packet_marker = 0;
    m_start_of_packet_marker_found = false;
  }

  void move_rear_pointer()
  {
    // add next char
    m_idx_end++; // move rear pointer
    char next_char = m_packet[m_idx_end]; // identify next char

    // update dico with next char
    if (m_signal_dico.find(next_char)==m_signal_dico.end())
      m_signal_dico[next_char] = 1; // add it if it doesnt exist
    else
      m_signal_dico[next_char]++; // increment count if it already exists
  }

  void move_front_pointer()
  {
    // 01234 // not ok
    // 45678 // not ok

    // should rear pointer or not
    if (m_idx_end-m_idx_start==4) // 4 means 5 chars considered
    {
      char remove_char = m_signal_dico[m_idx_start]; // identify char to remove

      // need to shorten
      if (m_signal_dico[remove_char]==1)
        m_signal_dico.erase(remove_char); // only 1 left, remove it from dico
      else
        m_signal_dico[remove_char]--; // more than 1 left, decrement count

      m_idx_start++; // increment rear pointer
    }

  }

  void is_start_marker_found()
  {
    if (m_signal_dico.size()==4)
      m_start_of_packet_marker_found = true;
  }

  void consider_next_char()
  {
    move_rear_pointer();     // consume next char
    move_front_pointer();    // only if needed
    is_start_marker_found(); // check if start marker found
  }

  void identify_start_of_packet_marker()
  {
    while (!m_start_of_packet_marker_found)
    {
      consider_next_char();
      utils::display_dico(m_signal_dico);
      if (m_start_of_packet_marker_found)
        m_start_of_packet_marker = m_idx_end;
    }

    std::cout << "start marker = " << m_start_of_packet_marker << std::endl;
    std::cout << "start signal = " << for (int i=m_idx_start;i<m_idx_end;i++) std::cout << m_packet[i];
    std::cout << std::endl;
  }


};


}

void day6_part1();
void day6_part2();

#endif // __DAY6_HPP
