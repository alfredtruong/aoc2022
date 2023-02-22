#ifndef __DAY10_HPP
#define __DAY10_HPP

namespace day10 {

class signal_decoder
{
private:
  std::vector<std::vector<std::string>> m_instructions;
  std::vector<int> m_signal;

public:
  signal_decoder(std::string filepath);
  void init_instructions();
  int signal_during_cycle(int i,bool verbose=false); // 1-indexed
  int signal_after_cycle(int i,bool verbose=false); // 1-indexed
  int signal_strength_during_cycle(int i,bool verbose);
  void sum_signal_strength_during_cycle();
  void show_signal_history();
  void do_noop();
  void do_addx(int x);
  void parse_instructions(std::string filepath);
  void do_instructions();
};


/*
//https://stackoverflow.com/questions/13249023/how-do-i-instantiate-an-object-inside-of-a-c-class
class class2
{
  public:
    class2() : class1Obj(1, 2, 3) {}
    // Destructor, copy constructor/assignment, etc...
  private:
    class1 class1Obj;
};
*/

class crt
{
private:
  static const int CRT_HEIGHT = 6;
  static const int CRT_WEIGHT = 40;
  char m_arr[CRT_HEIGHT][CRT_WEIGHT];
  signal_decoder *m_signal_decoder;

public:
  crt(std::string filepath)
  {
    m_signal_decoder = new signal_decoder(filepath);
  }

  bool should_draw_on_cycle(int cycle,int sprite_centre)
  {
    cycle = cycle%40;
    if (sprite_centre-1 <= cycle <= sprite_centre+1)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void draw_screen()
  {
    int cycle=1;
    for (int r=0;r<CRT_HEIGHT;r++)
    {
      for (int c=0;c<CRT_WEIGHT;r++)
      {
        int sprite_centre = m_signal_decoder.signal_during_cycle(cycle);

        // draw on this cycle if sprite overlaps
        if (should_draw_on_cycle(cycle,sprite_centre))
          m_arr[r][c]='#';

        // increment for next cycle
        cycle++;
      }
    }
  }
};


}

void day10_part1();
void day10_part2();

#endif // __DAY10_HPP
