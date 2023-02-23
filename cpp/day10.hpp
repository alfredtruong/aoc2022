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
  char m_arr[CRT_HEIGHT][CRT_WEIGHT] = {'.'};
  signal_decoder m_signal_decoder_instance; // (A) allocate memory for instance
  signal_decoder *m_signal_decoder_pointer; // (B) allocate memory for pointer to instance (not allocated)

public:
  // (Q) why does m_signal_decoder_instance need to be instantiated in initializer list?
  // (A) cos it doesnt have a default constructor
  // https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/
  crt(std::string filepath);
  ~crt();
  bool should_draw_on_this_cycle(int cycle,int sprite_centre,bool verbose=false);
  void decode_signal();
  void draw_screen();
};


}

void day10_part1();
void day10_part2();

#endif // __DAY10_HPP
