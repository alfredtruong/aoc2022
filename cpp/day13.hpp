#ifndef __DAY13_HPP
#define __DAY13_HPP

namespace day13 {

/*
struct PacketEntry
{
  bool isValue;
  int value;
  std::vector<PacketEntry>;
};

struct Packet
{
  std::vector<PacketEntry>

  void Packet(std::string str)
  {
    parse_packet(str);
  }

  void parse_packet(std::string str)
  {
    // ltrim '['
    // rtrim ']'
    // split on ','
    utils::split_string<PacketEntry>(str);
    // use PacketEntry constructor
  }
};

class ComparePackets
{
private:
  std::string m_packet1;
  std::string m_packet2;

};
class Packet
{
private:
  std::vector<Packet> m_packet_items;

public:
  Packet(std::string str)
  {
    int packet_start = 0;
    int packet_stop = str.length()-1;


  }

  void parse_packet_contents(std::string contents)
  {
    // strip away outer brackets
    if (contents.length()==0)
    {
      // done
    }
    else
    {
      // something to parse

    }
  }
};

class Packet
{
private:
  bool m_isValue
  int m_value;
  std::vector<Packet> m_items;

public:
  Packet(std::string str)
  {
    int packet_start = 0;
    int packet_stop = str.length()-1;
    while (packet_start != packet_stop)
    {
      int item_end;
      find_item_end(str,item_end)
      parse(std::string str);
    }
  }


  void parse(const std::string &str)
  {
    int stop_idx;
    find_item_end(str,stop_idx); // matching bracket or just next comma
    item_str = std::string(str(0,stop_idx));
    Packet item(item_str);
    m_contents.push_back()

  }

  std::vector<PacketContents> parse_bracket_contents(const std::string &str,int lbracket,int rbracket)
  {
    std::vector<PacketContents> out;
    while (lbracket!=rbracket)
    {
      int next_subpacket_start = find_next_subpacket(str,lbracket);
      std::string new_str = str(lbracket,rbracket);
      PacketContents pc(new_str);
      out.push_back(pc);
      lbracket = next_subpacket_start;
    }
    return out;
  }

  int find_next_subpacket
};
*/
}

void day13_part1();
void day13_part2();

#endif // __DAY13_HPP
