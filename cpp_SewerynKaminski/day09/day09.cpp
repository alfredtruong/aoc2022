#include "../utils.hpp"

#include <fstream> // std::fstream
#include <iostream>
#include <vector>
#include <list>

inline std::string test_input_1 =
R"(R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2)";


inline std::string test_input_2 =
R"(R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20)";

struct Point
{
  int16_t x=0,y=0;
  Point() : x(0),y(0) {} // default constructor with init list
  Point(const Point& p) : x(p.x), y(p.y) {} // copy constructor with init list
  Point(int16_t xx,int16_t yy) : x(xx), y(yy) {} // constructor with init list

  // operator overloading
  Point operator < (const Point& p) const {
    return Point(int16_t(x<p.x),int16_t(y<p.y));
  }
  bool operator == (const Point& p) const {
    return p.x==x && p.y==y;
  }
  Point& operator * (int s) {
    x *= s;
    y *= s;
    return *this;
  }
  Point operator - (const Point & p) {
    return {int16_t(x-p.x),int16_t(y-p.y};
  }
  Point& operator += (const Point & p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  Point& operator += (const Point && p) {
    x += p.x;
    y += p.y;
    return *this;
  }

  // functions
  auto abs() {
    return Point(std::abs(x),std::abs(y));
  }

  operator bool() { // wtf is this?
    return x || y;
  }
};

template<>
struct std::hash<Point>
{
  std::size_t operator() (const Point& p) const {
  }
};

void Task1(std::istream& file)
{
}

void Task2(std::istream& file)
{
}


void Task1_example()
{
  Task1(str_to_ss(test_input));
}
void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day09_1.txt");
  Task1(f);
  f.close();
}
void Task2_example()
{
  Task2(str_to_ss(test_input));
}
void Task2_actual()
{
  std::fstream f;
  f.open("../../input/day09_1.txt");
  Task2(f);
  f.close();
}

int main()
{
  Task1_example();
  Task1_actual();
  Task2_example();
  Task2_actual();
  return 0;
}
