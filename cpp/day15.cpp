#include "utils/utils.hpp"
#include "day15.hpp"

// https://github.com/Strunzdesign/advent-of-code/blob/main/2022/day15/main.cpp

namespace day15 {

std::pair<int,int> operator+(const std::pair<int,int>& p1,const std::pair<int,int>& p2)
{
    return std::pair<int,int>(p1.first+p2.first,p1.second+p2.second);
}

std::ostream& operator<<(std::ostream& o,const std::pair<int,int>&p)
{
  o << p.first << "/" << p.second;
  return o;
}

SensorData::SensorData(std::string filepath)
{
  parse_sensor_data(filepath);
  //std_for_each_1();
  //std_for_each_2();
  //std_for_each_3();
  identify_extremals();
}

void SensorData::parse_sensor_data(std::string filepath)
{
  // open file
  std::fstream f;
  f.open(filepath,std::ios::in);

  // read it
  std::string line;
  while (std::getline(f,line))
  {
    parse_sensor_line(line);
  }

  // close it
  f.close();
}

void SensorData::parse_sensor_line(std::string line)
{
  std::string sep;
  int start_pos = 0;
  int end_pos = 0;

  // sensor data
  sep = "x=";
  start_pos = line.find(sep,start_pos)+sep.length();
  sep = ",";
  end_pos = line.find(sep,start_pos);
  int sensor_x = std::stoi(line.substr(start_pos,end_pos));
  //std::cout << start_pos << " " << end_pos << " " << line.substr(start_pos,end_pos) << std::endl;

  sep = "y=";
  start_pos = line.find(sep,end_pos)+sep.length();
  sep = ":";
  end_pos = line.find(sep,start_pos);
  int sensor_y = std::stoi(line.substr(start_pos,end_pos));

  // beacon data
  sep = "x=";
  start_pos = line.find(sep,end_pos)+sep.length();
  sep = ",";
  end_pos = line.find(",",start_pos);
  int beacon_x = std::stoi(line.substr(start_pos,end_pos));

  sep = "y=";
  start_pos = line.find(sep,end_pos)+sep.length();
  int beacon_y = std::stoi(line.substr(start_pos));

  //std::cout << sensor_x << "/" << sensor_y << " "  << beacon_x << "/" << beacon_y << std::endl; //

  // save down data
  Location s(sensor_x,sensor_y);
  Location b(beacon_x,beacon_y);

  // below implementation is ordered
  m_sensor_locations.insert(s);
  m_beacon_locations.insert(b);
  int dist = manhattan_distance(s,b);
  m_nearest_beacon_distance[s] = dist;

  std::cout << "sensor = " << s << ", beacon = " << b << ", distance = " << dist << std::endl;
}

void SensorData::update_extremals(std::pair<int,int> p)
{
  if (!m_extremals_initialized)
    {
    m_extremals_initialized = true;

    m_x_min = p.first;
    m_x_max = p.first;
    m_y_min = p.second;
    m_y_max = p.second;
  }
  else
  {
    if (p.first < m_x_min) m_x_min = p.first;
    if (p.first > m_x_max) m_x_max = p.first;
    if (p.second < m_y_min) m_y_min = p.second;
    if (p.second > m_y_max) m_y_max = p.second;
  }

  std::cout << "[" << p << "]" <<
  " x-range = (" << m_x_min << "/" << m_x_max << ")" <<
  " y-range = (" << m_y_min << "/" << m_y_max << ")" <<
  std::endl;
}

/*
void identify_extremals()
{
  for (auto& sensor : m_sensor_locations)
    update_extremals(sensor);

  for (auto& beacon : m_beacon_locations)
    update_extremals(beacon);
}
*/

void SensorData::identify_extremals()
{
  for (auto& sensor : m_sensor_locations)
  {
    int sensor_range = m_nearest_beacon_distance[sensor];
    update_extremals(sensor + std::pair<int,int>(-sensor_range,0)); // left extremal
    update_extremals(sensor + std::pair<int,int>(sensor_range,0)); // right extremal
    update_extremals(sensor + std::pair<int,int>(0,-sensor_range)); // top extremal
    update_extremals(sensor + std::pair<int,int>(0,sensor_range)); // bottom extremal
  }
}

int SensorData::manhattan_distance(const auto& p1,const auto& p2)
{
  return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

void SensorData::possible_locations_on_row(int row,int search_range,bool verbose)
{
  std::vector<Location> possible_locations;

  int n_not_possible_points = 0;
  // build up string
  std::stringstream s;

  for (int i=m_x_min;i<=m_x_max;i++)
  {
    bool is_on_sensor = false;
    bool is_on_beacon = false;
    bool is_in_range = false;
    std::pair<int,int> p(i,row);

//      if (m_nearest_beacon_distance.find(p)!=m_nearest_beacon_distance.end())
    if (m_sensor_locations.find(p)!=m_sensor_locations.end())
    {
      // check if location has a sensor
      is_on_sensor = true;
      if (verbose) std::cout << "x = " << p << ", SENSOR LOCATED HERE" << std::endl;
    }
    else if (m_beacon_locations.find(p)!=m_beacon_locations.end())
    {
      // check if location has a sensor
      is_on_beacon = true;
      if (verbose) std::cout << "x = " << p << ", BEACON LOCATED HERE" << std::endl;
    }
    else
    {
      for (auto& sensor : m_sensor_locations)
      {
        // otherwise check if is in range
        int dist = manhattan_distance(sensor,p);
        if (dist <= m_nearest_beacon_distance[sensor])
        {
          is_in_range = true;
          n_not_possible_points++;
          if (verbose) std::cout << "x = " << p << ", sensor = " << sensor << ", sensor nearest = " << m_nearest_beacon_distance[sensor] << ", my dist = " << dist << std::endl;
          break;
        }
      }
    }
    // this x
    if (is_on_sensor)
    {
      s << 'S';
    }
    else if (is_on_beacon)
    {
      s << 'B';
    }
    else
    {
      if (is_in_range)
        s << '#';
      else
      {
        s << '.';
        if (p.first >=0 && p.first <= search_range && p.second >=0 && p.second <= search_range)
        {
          //std::cout << p << std::endl;
          possible_locations.push_back(p);
        }
      }
    }
  }

  std::cout << "[" << row << "]\t" << s.str() << " n_not_possible_points = " << n_not_possible_points << std::endl;
  for (auto& possible_location : possible_locations)
  {
    std::cout << possible_location << " : " << tuning_frequency(possible_location) << std::endl;
  }
}

int SensorData::tuning_frequency(const Location& p)
{
  return p.first * 4000000 + p.second;
}

void SensorData::show_nearest_beacon_distances()
{
  for (auto& [location,dist] : m_nearest_beacon_distance)
    std::cout << location << " : " << dist << std::endl;
}

/*
void SensorData::std_for_each_3()
{
  std::cout << __func__ << std::endl;
  std::cout << m_nearest_beacon_distance.size() << std::endl;

  // for_each = unordered show
  std::for_each(m_nearest_beacon_distance.begin(),m_nearest_beacon_distance.end(),[](const auto& sensor){std::cout << sensor.first.first << "/" << sensor.first.second << std::endl;});
  std::cout << std::endl;

  // for_each = ordered show
  auto& local_sensor_locations = m_nearest_beacon_distance; // lambda can only get local variables, not global ones
  std::for_each(m_sensor_locations.begin(),m_sensor_locations.end(),[local_sensor_locations](const auto& sensor){std::cout << local_sensor_locations.at(sensor).first << std::endl;});
  std::cout << std::endl;

  // this doesnt work cos lambda functions can only access local variables, not global ones
  // for_each = ordered show
  // std::for_each(m_sensor_locations.begin(),m_sensor_locations.end(),[m_nearest_beacon_distance](const auto& sensor){std::cout << m_nearest_beacon_distance.at(sensor).first << std::endl;});
  // std::cout << std::endl;

  // for loop = ordered show without lambda function
  for (const auto& sensor : m_sensor_locations)
  {
    std::cout << m_nearest_beacon_distance[sensor].first << "/" << m_nearest_beacon_distance[sensor].second << std::endl;
  }
  std::cout << std::endl;

  // for loop with named bindings (C++17) = ordered show without lambda function
  for (const auto& [sensor_location,beacon_location] : m_nearest_beacon_distance)
  {
    std::cout << sensor_location.first << "/" << sensor_location.second << std::endl;
    std::cout << beacon_location.first << "/" << beacon_location.second << std::endl;
  }
  std::cout << std::endl;
}
*/

void SensorData::std_for_each_2()
{
  std::for_each(
                m_nearest_beacon_distance.begin(),
                m_nearest_beacon_distance.end(),
                [](const auto& sensor){std::cout << "hi" << std::endl;}
  );

  std::vector<int> alfred {1,2,3,4,5};
  std::for_each(alfred.begin(),alfred.end(),[](int& n){std::cout << n << " " << std::endl;});
  std::for_each(alfred.begin(),alfred.end(),[](int& n){n*=-1;}); // this actually changed alfred container
  std::for_each(alfred.begin(),alfred.end(),[](int& n){std::cout << n << " " << std::endl;});

  int i=0;
  /*
  std::for_each(alfred.begin(),alfred.end(),[=](int& n){i++;}); // pass by val // doesnt work, is passed by const
  std::cout << "i=" << std::endl;
  */
  i=0;
  std::for_each(alfred.begin(),alfred.end(),[&](int& n){i++;}); // pass by ref
  std::cout << "i=" << i << std::endl;
}

void SensorData::std_for_each_1()
{
  std::vector<int> v {3, -4, 2, -8, 15, 267};
  auto print = [](const int& n) { std::cout << n << ' '; };

  std::cout << "before:\t";
  std::for_each(v.cbegin(), v.cend(), print);
  std::cout << '\n';

  // increment elements in-place
  std::for_each(v.begin(), v.end(), [](int &n){ n++; });

  std::cout << "after:\t";
  std::for_each(v.cbegin(), v.cend(), print);
  std::cout << '\n';

  struct Sum
  {
      void operator()(int n) { sum += n; }
      int sum{0};
  };

  // invoke Sum::operator() for each element
  Sum s = std::for_each(v.cbegin(), v.cend(), Sum());
  std::cout << "sum:\t" << s.sum << '\n';
}

void part_1_ex1()
{
  std::cout << "part 1 example" << std::endl;
  SensorData sd("../input/day15_ex.txt");
  sd.possible_locations_on_row(9);
  sd.possible_locations_on_row(10);
  sd.possible_locations_on_row(11);
}

void part_1()
{
  std::cout << "part 1" << std::endl;
  SensorData sd("../input/day15_1.txt");
  sd.possible_locations_on_row(2000000);
}

void part_2_ex2()
{
  std::cout << "part 2 example" << std::endl;
  SensorData sd("../input/day15_ex.txt");
  for (int i=0;i<=20;i++)
    sd.possible_locations_on_row(i,20);
}

void part_2()
{
  std::cout << "part 2" << std::endl;
  SensorData sd("../input/day15_1.txt");
  sd.show_nearest_beacon_distances();
  /*
  for (int i=0;i<=4000000;i++)
  {
    for (int j=0;j<=4000000;j++)
    {
      int i;
    }
    if (i%10000==0) std::cout << "i=" << i << std::endl;
  }
  */
}



}

void day15_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day15::part_1_ex1();
  //day15::part_1();
}

void day15_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day15::part_2_ex2();
  day15::part_2();
}

