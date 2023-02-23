#include "utils/utils.hpp"
#include "day10.hpp"

namespace day10 {


signal_decoder::signal_decoder(std::string filepath)
{
  init_instructions();
  parse_instructions(filepath);
  do_instructions();
}

void signal_decoder::init_instructions()
{
  m_signal.push_back(1); // start of cycle 1
  m_signal.push_back(1); // end of cycle 2
}

int signal_decoder::signal_during_cycle(int i,bool verbose) // 1-indexed
{
  int out = m_signal[i];
  if (verbose) std::cout << "[signal during " << i << "]\t" << out << std::endl;
  return out;
}

int signal_decoder::signal_after_cycle(int i,bool verbose) // 1-indexed
{
  int out = m_signal[i+1];
  if (verbose) std::cout << "[signal after " << i << "]\t" << out << std::endl;
  return out;
}

int signal_decoder::signal_strength_during_cycle(int i,bool verbose)
{
  return signal_during_cycle(i,verbose) * i;
}

void signal_decoder::sum_signal_strength_during_cycle()
{
  int total=0;
  for (auto i : {20,60,100,140,180,220})
  {
    total+=signal_strength_during_cycle(i,true);
  }
  std::cout << "sum signal strength = " << total << std::endl;
}

void signal_decoder::show_signal_history()
{
  for (int i=1;i<=m_signal.size();i++)
    std::cout << "\t[during " << i << "]\t" << signal_during_cycle(i) << " " << "\t[after " << i << "]\t" << signal_after_cycle(i) << std::endl;
}

void signal_decoder::do_noop()
{
  m_signal.push_back(m_signal.back());
}

void signal_decoder::do_addx(int x)
{
  do_noop();
  m_signal.push_back(m_signal.back()+x);
}

void signal_decoder::parse_instructions(std::string filepath)
{
  m_instructions = utils::parse_file<std::string>(filepath,' ',false);
}

void signal_decoder::do_instructions()
{
  for (auto instruction : m_instructions)
  {
    std::string action = instruction[0];

    if (action=="noop")
    {
      do_noop();
    }
    else if (action=="addx")
    {
      int x = std::stoi(instruction[1]);
      do_addx(x);
    }
    else
    {
      std::cout << "[instruction not recognized] " << action << std::endl;
      exit(1);
    }
  }
}

crt::crt(std::string filepath) : m_signal_decoder_instance(filepath) // (A) instantiate instance
{
  //m_signal_decoder_instance(filepath);
  m_signal_decoder_pointer = new signal_decoder(filepath); // (B) allocate instance on heap
  decode_signal();
  draw_screen();
}

crt::~crt()
{
  delete m_signal_decoder_pointer;
}

bool crt::should_draw_on_this_cycle(int cycle,int sprite_centre,bool verbose)
{
  bool should_draw;
  int x_position = (cycle-1)%40;
  if ((sprite_centre-1 <= x_position) && (x_position <= sprite_centre+1))
    should_draw=true;
  else
    should_draw=false;

  if (verbose)
    std::cout << __func__ <<
    "[" << cycle << "]" <<
    " sprite_centre=" << sprite_centre <<
    " x_position=" << x_position <<
    " should_draw=" << should_draw <<
    std::endl;

  return should_draw;
}

void crt::decode_signal()
{
  int cycle=1;
  for (int r=0;r<CRT_HEIGHT;r++)
  {
    for (int c=0;c<CRT_WEIGHT;c++)
    {
      int sprite_centre = m_signal_decoder_pointer->signal_during_cycle(cycle);

      // draw on this cycle if sprite overlaps
      if (should_draw_on_this_cycle(cycle,sprite_centre))
        m_arr[r][c]='#';
      else
        m_arr[r][c]='.';

      // increment for next cycle
      //draw_screen();
      cycle++;
    }
  }
}

void crt::draw_screen()
{
  for (int r=0;r<CRT_HEIGHT;r++)
  {
    for (int c=0;c<CRT_WEIGHT;c++)
    {
      std::cout << m_arr[r][c];
    }
    std::cout << std::endl;
  }
}

void part_1_ex1()
{
  std::cout << "part 1 example 1" << std::endl;

  signal_decoder s("../input/day10_ex1.txt");
  s.show_signal_history();
}

void part_1_ex2()
{
  std::cout << "part 1 example 2" << std::endl;

  signal_decoder s("../input/day10_ex2.txt");
  s.sum_signal_strength_during_cycle();
}

void part_1_sum_signal_strength()
{
  std::cout << "part 1" << std::endl;

  signal_decoder s("../input/day10_1.txt");
  s.sum_signal_strength_during_cycle();
}

void part_2_ex2()
{
  std::cout << "part 2 example" << std::endl;

  crt c("../input/day10_ex2.txt");
}

void part_2_crt_output()
{
  std::cout << "part 2" << std::endl;

  crt c("../input/day10_1.txt");
}

}

void day10_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day10::part_1_ex1();
  day10::part_1_ex2();
  day10::part_1_sum_signal_strength();
}

void day10_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day10::part_2_ex2();
  day10::part_2_crt_output();
}
