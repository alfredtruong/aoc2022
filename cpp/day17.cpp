#include "utils/utils.hpp"
#include "day17.hpp"

namespace day17 {


Cave::Cave(std::string filepath)
{

  std::fstream f;
  f.open(filepath,std::ios::in);
  std::getline(f,m_blow);

  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  drop_one_shape(true);
  //add_test();
  //blow_minus_test();
  //blow_plus_test();
  //blow_el_test();
  //blow_pipe_test();
  //blow_block_test();
  //drop_minus_test();
  //drop_plus_test();
  //drop_el_test();
  //drop_pipe_test();
  //drop_block_test();

  f.close();
}

void Cave::drop_minus_test()
{
  add_minus();
  show_cave();
  drop_minus();
  show_cave();
  drop_minus();
  show_cave();
  drop_minus();
  show_cave();
  drop_minus();
  show_cave();
  drop_minus();
  show_cave();
  drop_minus();
  show_cave();
}

void Cave::drop_plus_test()
{
  add_plus();
  show_cave();
  drop_plus();
  show_cave();
  drop_plus();
  show_cave();
  drop_plus();
  show_cave();
  drop_plus();
  show_cave();
  drop_plus();
  show_cave();
}

void Cave::drop_el_test()
{
  add_el();
  show_cave();
  drop_el();
  show_cave();
  drop_el();
  show_cave();
  drop_el();
  show_cave();
  drop_el();
  show_cave();
  drop_el();
  show_cave();
}

void Cave::drop_pipe_test()
{
  add_pipe();
  show_cave();
  drop_pipe();
  show_cave();
  drop_pipe();
  show_cave();
  drop_pipe();
  show_cave();
  drop_pipe();
  show_cave();
  drop_pipe();
  show_cave();
}

void Cave::drop_block_test()
{
  bool verbose = true;
  add_block();
  show_cave();
  drop_block();
  show_cave();
  drop_block();
  show_cave();
  drop_block();
  show_cave();
  drop_block();
  show_cave();
  drop_block();
  show_cave();
}


void Cave::add_test() {
  add_minus();
  show_cave();
  m_contents.clear();

  add_plus();
  show_cave();
  m_contents.clear();

  add_el();
  show_cave();
  m_contents.clear();

  add_pipe();
  show_cave();
  m_contents.clear();

  add_block();
  show_cave();
  m_contents.clear();
}

void Cave::blow_minus_test()
{
  bool verbose = true;
  add_minus();
  show_cave();
  blow_minus(true,verbose);
  blow_minus(true,verbose);
  blow_minus(true,verbose);
  blow_minus(true,verbose);
  blow_minus(true,verbose);
  blow_minus(false,verbose);
  blow_minus(false,verbose);
  blow_minus(false,verbose);
  blow_minus(false,verbose);
  blow_minus(false,verbose);
  blow_minus(false,verbose);
  show_cave();
}

void Cave::blow_plus_test()
{
  bool verbose = true;
  add_plus();
  show_cave();
  blow_plus(true,verbose);
  blow_plus(true,verbose);
  blow_plus(true,verbose);
  blow_plus(true,verbose);
  blow_plus(true,verbose);
  blow_plus(true,verbose);
  blow_plus(false,verbose);
  blow_plus(false,verbose);
  blow_plus(false,verbose);
  blow_plus(false,verbose);
  blow_plus(false,verbose);
  blow_plus(false,verbose);
  show_cave();
}

void Cave::blow_el_test()
{
  bool verbose = true;
  add_el();
  show_cave();
  blow_el(true,verbose);
  blow_el(true,verbose);
  blow_el(true,verbose);
  blow_el(true,verbose);
  blow_el(true,verbose);
  blow_el(true,verbose);
  blow_el(false,verbose);
  blow_el(false,verbose);
  blow_el(false,verbose);
  blow_el(false,verbose);
  blow_el(false,verbose);
  blow_el(false,verbose);
  show_cave();
}

void Cave::blow_pipe_test()
{
  bool verbose = true;
  add_pipe();
  show_cave();
  blow_pipe(true,verbose);
  blow_pipe(true,verbose);
  blow_pipe(true,verbose);
  blow_pipe(true,verbose);
  blow_pipe(true,verbose);
  blow_pipe(true,verbose);
  blow_pipe(false,verbose);
  blow_pipe(false,verbose);
  blow_pipe(false,verbose);
  blow_pipe(false,verbose);
  blow_pipe(false,verbose);
  blow_pipe(false,verbose);
  show_cave();
}

void Cave::blow_block_test()
{
  bool verbose = true;
  add_block();
  show_cave();
  blow_block(true,verbose);
  blow_block(true,verbose);
  blow_block(true,verbose);
  blow_block(true,verbose);
  blow_block(true,verbose);
  blow_block(true,verbose);
  blow_block(false,verbose);
  blow_block(false,verbose);
  blow_block(false,verbose);
  blow_block(false,verbose);
  blow_block(false,verbose);
  blow_block(false,verbose);
  show_cave();
}

void Cave::show_line(const auto& line,std::string blurb)
{
  for (int i=0;i<WIDTH;i++)
  {
    if (line[i])
      std::cout << '#';
    else
      std::cout << '.';
  }

  std::cout << blurb;
}

void Cave::show_cave()
{
  std::cout <<
  "height = " << m_contents.size() <<
  ", rock settled = " << m_rock_is_settled <<
  ", rock bottom lhs = " << m_rock_bottom_lhs <<
  ", rock bottom lhs = " << m_rock_bottom_rhs <<
  std::endl;

  for (auto it=m_contents.rbegin();it!=m_contents.rend();it++)
  {
    show_line(*it,"");
    std::cout << "\t" << (*it).any() << std::endl;
  }

}

void Cave::add()
{
  switch (m_rock_idx)
  {
  case 0:
    add_minus();
    break;
  case 1:
    add_plus();
    break;
  case 2:
    add_el();
    break;
  case 3:
    add_pipe();
    break;
  case 4:
    add_block();
    break;
  }

  m_rock_is_settled = false;

}

void Cave::add_minus()
{
  m_rock_is_settled = false;
  m_rock_bottom_lhs = 2;
  m_rock_bottom_rhs = 5;

  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0111100);
}

void Cave::add_plus()
{
  m_rock_is_settled = false;
  m_rock_bottom_lhs = 3;
  m_rock_bottom_rhs = 3;

  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0001000);
  m_contents.emplace_back(0b0011100);
  m_contents.emplace_back(0b0001000);
}

void Cave::add_el()
{
  m_rock_is_settled = false;
  m_rock_bottom_lhs = 2;
  m_rock_bottom_rhs = 4;

  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0011100);
  m_contents.emplace_back(0b0010000);
  m_contents.emplace_back(0b0010000);
}

void Cave::add_pipe()
{
  m_rock_is_settled = false;
  m_rock_bottom_lhs = 2;
  m_rock_bottom_rhs = 2;

  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0000100);
  m_contents.emplace_back(0b0000100);
  m_contents.emplace_back(0b0000100);
  m_contents.emplace_back(0b0000100);
}

void Cave::add_block()
{
  m_rock_is_settled = false;
  m_rock_bottom_lhs = 2;
  m_rock_bottom_rhs = 3;

  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0001100);
  m_contents.emplace_back(0b0001100);
}

bool Cave::is_line_empty(auto& line)
{
    return !line.any();
}

void Cave::blow(bool is_left)
{
  switch (m_rock_idx)
  {
  case 0:
    blow_minus(is_left);
    break;
  case 1:
    blow_plus(is_left);
    break;
  case 2:
    blow_el(is_left);
    break;
  case 3:
    blow_pipe(is_left);
    break;
  case 4:
    blow_block(is_left,true);
    break;
  }
}

void Cave::move_from_to(auto& line,int from_idx,int to_idx)
{
  line[from_idx]=false;
  line[to_idx]=true;
}

void Cave::blow_minus(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // only care about top line
  auto& line = m_contents.back();

  // care about 3 lines
  // show_line(line);

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_lhs>0)
    {
      if (!line[m_rock_bottom_lhs-1])
      {
        move_from_to(line,m_rock_bottom_rhs,m_rock_bottom_lhs-1);
        m_rock_bottom_lhs--;
        m_rock_bottom_rhs--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose) show_line(line,blurb.str());
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_rhs<(WIDTH-1))
    {
      if (!line[m_rock_bottom_rhs+1])
      {
        move_from_to(line,m_rock_bottom_lhs,m_rock_bottom_rhs+1);
        m_rock_bottom_lhs++;
        m_rock_bottom_rhs++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose) show_line(line,blurb.str());
  }
}

void Cave::blow_plus(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 3 lines
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);
  auto& line3 = *(--iter);

  //show_line(line1);
  //show_line(line2);
  //show_line(line3);

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_lhs>1)
    {
      if (
        !line1[m_rock_bottom_lhs-1  ] &&
        !line2[m_rock_bottom_lhs-1-1] &&
        !line3[m_rock_bottom_lhs-1  ]
      )
      {
        move_from_to(line1,m_rock_bottom_rhs,  m_rock_bottom_lhs-1  );
        move_from_to(line2,m_rock_bottom_rhs+1,m_rock_bottom_lhs-1-1);
        move_from_to(line3,m_rock_bottom_rhs,  m_rock_bottom_lhs-1  );
        m_rock_bottom_lhs--;
        m_rock_bottom_rhs--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_rhs<(WIDTH-1-1))
    {
      if (
        !line1[m_rock_bottom_rhs+1  ] &&
        !line2[m_rock_bottom_rhs+1+1] &&
        !line3[m_rock_bottom_rhs+1  ]
      )
      {
        move_from_to(line1,m_rock_bottom_lhs,  m_rock_bottom_rhs+1  );
        move_from_to(line2,m_rock_bottom_lhs-1,m_rock_bottom_rhs+1+1);
        move_from_to(line3,m_rock_bottom_lhs,  m_rock_bottom_rhs+1  );
        m_rock_bottom_lhs++;
        m_rock_bottom_rhs++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
}

void Cave::blow_el(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 3 lines
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);
  auto& line3 = *(--iter);

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_lhs>0)
    {
      if (
        !line1[m_rock_bottom_lhs-1+2] &&
        !line2[m_rock_bottom_lhs-1+2] &&
        !line3[m_rock_bottom_lhs-1  ]
      )
      {
        move_from_to(line1,m_rock_bottom_rhs,m_rock_bottom_rhs-1);
        move_from_to(line2,m_rock_bottom_rhs,m_rock_bottom_rhs-1);
        move_from_to(line3,m_rock_bottom_rhs,m_rock_bottom_lhs-1);
        m_rock_bottom_lhs--;
        m_rock_bottom_rhs--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_rhs<(WIDTH-1))
    {
      if (
        !line1[m_rock_bottom_rhs+1] &&
        !line2[m_rock_bottom_rhs+1] &&
        !line3[m_rock_bottom_rhs+1]
      )
      {
        move_from_to(line1,m_rock_bottom_rhs,m_rock_bottom_rhs+1);
        move_from_to(line2,m_rock_bottom_rhs,m_rock_bottom_rhs+1);
        move_from_to(line3,m_rock_bottom_lhs,m_rock_bottom_rhs+1);
        m_rock_bottom_lhs++;
        m_rock_bottom_rhs++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
}


void Cave::blow_pipe(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 4 lines
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);
  auto& line3 = *(--iter);
  auto& line4 = *(--iter);

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_lhs>0)
    {
      if (
        !line1[m_rock_bottom_lhs-1] &&
        !line2[m_rock_bottom_lhs-1] &&
        !line3[m_rock_bottom_lhs-1] &&
        !line4[m_rock_bottom_lhs-1]
      )
      {
        move_from_to(line1,m_rock_bottom_lhs,m_rock_bottom_lhs-1);
        move_from_to(line2,m_rock_bottom_lhs,m_rock_bottom_lhs-1);
        move_from_to(line3,m_rock_bottom_lhs,m_rock_bottom_lhs-1);
        move_from_to(line4,m_rock_bottom_lhs,m_rock_bottom_lhs-1);
        m_rock_bottom_lhs--;
        m_rock_bottom_rhs--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
      show_line(line4,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_rhs<(WIDTH-1))
    {
      if (
        !line1[m_rock_bottom_rhs+1] &&
        !line2[m_rock_bottom_rhs+1] &&
        !line3[m_rock_bottom_rhs+1] &&
        !line4[m_rock_bottom_rhs+1]
      )
      {
        move_from_to(line1,m_rock_bottom_rhs,m_rock_bottom_rhs+1);
        move_from_to(line2,m_rock_bottom_rhs,m_rock_bottom_rhs+1);
        move_from_to(line3,m_rock_bottom_rhs,m_rock_bottom_rhs+1);
        move_from_to(line4,m_rock_bottom_rhs,m_rock_bottom_rhs+1);
        m_rock_bottom_lhs++;
        m_rock_bottom_rhs++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
      show_line(line4,blurb.str());
    }
  }
}

void Cave::blow_block(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 4 lines
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_lhs>0)
    {
      if (
        !line1[m_rock_bottom_lhs-1] &&
        !line2[m_rock_bottom_lhs-1]
      )
      {
        move_from_to(line1,m_rock_bottom_rhs,m_rock_bottom_lhs-1);
        move_from_to(line2,m_rock_bottom_rhs,m_rock_bottom_lhs-1);
        m_rock_bottom_lhs--;
        m_rock_bottom_rhs--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_bottom_rhs<(WIDTH-1))
    {
      if (
        !line1[m_rock_bottom_rhs+1] &&
        !line2[m_rock_bottom_rhs+1]
      )
      {
        move_from_to(line1,m_rock_bottom_lhs,m_rock_bottom_rhs+1);
        move_from_to(line2,m_rock_bottom_lhs,m_rock_bottom_rhs+1);
        m_rock_bottom_lhs++;
        m_rock_bottom_rhs++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
    }
  }
}


void Cave::drop_one_shape(bool verbose)
{
  add();
  if (verbose) show_cave();
  do
  {
    blow_once(verbose);
    drop_once();
    if (verbose) show_cave();
  } while (!m_rock_is_settled);
}

void Cave::blow_once(bool verbose)
{
  if (m_blow[m_blow_idx] == '<')
  {
    if (verbose) std::cout << "<" << std::endl;
    blow(true);
  }
  else
  {
    if (verbose) std::cout << ">" << std::endl;
    blow(false);
  }

  m_blow_idx = (m_blow_idx+1) % m_blow.length();
}

void Cave::drop_once()
{
  switch (m_rock_idx)
  {
  case 0:
    drop_minus();
    break;
  case 1:
    drop_plus();
    break;
  case 2:
    drop_el();
    break;
  case 3:
    drop_pipe();
    break;
  case 4:
    drop_block(true);
    break;
  }

  if (m_rock_is_settled)
    m_rock_idx = (m_rock_idx+1)%5;
}

void Cave::drop_minus()
{
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& below = *(--iter);

  // check if will settle
  if (
    m_contents.size()==1 ||
    below[m_rock_bottom_lhs  ] ||
    below[m_rock_bottom_lhs+1] ||
    below[m_rock_bottom_lhs+2] ||
    below[m_rock_bottom_lhs+3]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_bottom_lhs  ]=true;
    below[m_rock_bottom_lhs+1]=true;
    below[m_rock_bottom_lhs+2]=true;
    below[m_rock_bottom_lhs+3]=true;

    // zap top
    line1[m_rock_bottom_lhs  ]=false;
    line1[m_rock_bottom_lhs+1]=false;
    line1[m_rock_bottom_lhs+2]=false;
    line1[m_rock_bottom_lhs+3]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}


void Cave::drop_plus()
{
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);
  auto& line3 = *(--iter);
  auto& below = *(--iter);

  // check if will settle
  if (
    m_contents.size()==3 ||
    below[m_rock_bottom_lhs-1] ||
    below[m_rock_bottom_lhs  ] ||
    below[m_rock_bottom_lhs+1]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    line3[m_rock_bottom_lhs-1]=true;
    below[m_rock_bottom_lhs  ]=true;
    line3[m_rock_bottom_lhs+1]=true;

    // zap top
    line2[m_rock_bottom_lhs-1]=false;
    line1[m_rock_bottom_lhs  ]=false;
    line2[m_rock_bottom_lhs+1]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void Cave::drop_el()
{
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);
  auto& line3 = *(--iter);
  auto& below = *(--iter);

  // check if will settle
  if (
    m_contents.size()==3 ||
    below[m_rock_bottom_lhs  ] ||
    below[m_rock_bottom_lhs+1] ||
    below[m_rock_bottom_lhs+2]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_bottom_lhs  ]=true;
    below[m_rock_bottom_lhs+1]=true;
    below[m_rock_bottom_lhs+2]=true;

    // zap top
    line3[m_rock_bottom_lhs  ]=false;
    line3[m_rock_bottom_lhs+1]=false;
    line1[m_rock_bottom_lhs+2]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void Cave::drop_pipe()
{
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);
  auto& line3 = *(--iter);
  auto& line4 = *(--iter);
  auto& below = *(--iter);

  // check if will settle
  if (
    m_contents.size()==4 ||
    below[m_rock_bottom_lhs]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_bottom_lhs]=true;

    // zap top
    line1[m_rock_bottom_lhs]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void Cave::drop_block()
{
  auto iter = m_contents.end();
  auto& line1 = *(--iter);
  auto& line2 = *(--iter);
  auto& below = *(--iter);

  // check if will settle
  if (
    m_contents.size()==2 ||
    below[m_rock_bottom_lhs  ] ||
    below[m_rock_bottom_lhs+1]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_bottom_lhs  ]=true;
    below[m_rock_bottom_lhs+1]=true;

    // zap top
    line1[m_rock_bottom_lhs  ]=false;
    line1[m_rock_bottom_lhs+1]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void part_1_ex1()
{
  std::cout << "part 1 example" << std::endl;
  Cave c("../input/day17_ex.txt");
}

void part_1()
{
  std::cout << "part 1" << std::endl;
}

void part_2_ex2()
{
  std::cout << "part 2 example" << std::endl;
}

void part_2()
{
  std::cout << "part 2" << std::endl;
}



}

void day17_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day17::part_1_ex1();
  day17::part_1();
}

void day17_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day17::part_2_ex2();
  day17::part_2();
}
