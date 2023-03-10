#include "../utils.hpp"

#include <vector>
#include <fstream> // std::fstream
#include <string>

inline std::string test_input =
    R"(Sensor at x=2, y=18: closest beacon is at x=-2, y=15
Sensor at x=9, y=16: closest beacon is at x=10, y=16
Sensor at x=13, y=2: closest beacon is at x=15, y=3
Sensor at x=12, y=14: closest beacon is at x=10, y=16
Sensor at x=10, y=20: closest beacon is at x=10, y=16
Sensor at x=14, y=17: closest beacon is at x=10, y=16
Sensor at x=8, y=7: closest beacon is at x=2, y=10
Sensor at x=2, y=0: closest beacon is at x=2, y=10
Sensor at x=0, y=11: closest beacon is at x=2, y=10
Sensor at x=20, y=14: closest beacon is at x=25, y=17
Sensor at x=17, y=20: closest beacon is at x=21, y=22
Sensor at x=16, y=7: closest beacon is at x=15, y=3
Sensor at x=14, y=3: closest beacon is at x=15, y=3
Sensor at x=20, y=1: closest beacon is at x=15, y=3)";

std::string getLine(std::istream& file)
{
  std::string line;
  getline(file,line);
  return line;
}

struct Point{
    int x=0,y=0;
    Point(){}
    Point(int xx, int yy){x=xx,y=yy;}
    Point operator-(const Point& p){
        return {x-p.x,y-p.y};
    }
    bool operator ==(const Point& p ) const {
        return x==p.x && y==p.y;
    }
};

struct Sensor{
    Point p, b;
    int r=0;
    Sensor ( const Point& aa, const Point& bb ) {
        p = aa;
        b = bb;
        radius();
    }

    void radius(){
        r = abs(p.x - b.x)+abs(p.y - b.y);
    }
};

void Task1(std::istream& file)
{
  auto ans = 0;

  std::vector<Sensor> sensors;
  std::string line;
  while(std::getline(file,line))
  {
    std::stringstream ss( line );
    std::string t,sx,sy,bx,by;
    Point s, b;
    ss >> t >> t >> sx >> sy
       >> t >> t >> t >> t >> bx >> by;

    s.x = std::stoi ( sx.substr ( 2 ) );
    s.y = std::stoi ( sy.substr ( 2 ) );
    b.x = std::stoi ( bx.substr ( 2 ) );
    b.y = std::stoi ( by.substr ( 2 ) );

    std::cout << sx.substr ( 2 ) << " " << s.x << std::endl;
    std::cout << sy.substr ( 2 ) << " " << s.y << std::endl;
    std::cout << bx.substr ( 2 ) << " " << b.x << std::endl;
    std::cout << by.substr ( 2 ) << " " << b.y << std::endl;

    Sensor se ( s, b );
    sensors.push_back( se );
  }
}

void Task2(std::istream& file)
{
}

void Task1_example(std::string str)
{
  Task1(str_to_ss(str));
}

void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day15_1.txt");
  Task1(f);
  f.close();
}

void Task2_example(std::string str)
{
  Task2(str_to_ss(str));
}

void Task2_actual()
{
  std::fstream f;
  f.open("../../input/day15_1.txt");
  Task2(f);
  f.close();
}

int main()
{
  Task1_example(test_input);
  //Task1_actual();

  //Task2_example(test_input);
  //Task2_actual();
  return 0;
}
