#ifndef __DAY15_HPP
#define __DAY15_HPP

#include <algorithm>

namespace day15 {

typedef std::pair<int,int> Location;

std::pair<int,int> operator+(const std::pair<int,int>& p1,const std::pair<int,int>& p2); // overload pair adding
std::ostream& operator<<(std::ostream& o,const std::pair<int,int>&p); // overload pair displaying

class SensorData
{
private:
  std::set<Location> m_sensor_locations;
  std::set<Location> m_beacon_locations;
  std::map<Location,int> m_nearest_beacon_distance; // unorder_map requires a hashing function, map does not, why?
  bool m_extremals_initialized = false;
  int m_x_min,m_x_max;
  int m_y_min,m_y_max;

public:
  SensorData(std::string filepath);
  void parse_sensor_data(std::string filepath);
  void parse_sensor_line(std::string line);
  void update_extremals(std::pair<int,int> p);
  /*
  void identify_extremals()
  {
    for (auto& sensor : m_sensor_locations)
      update_extremals(sensor);

    for (auto& beacon : m_beacon_locations)
      update_extremals(beacon);
  }
  */

  void identify_extremals();
  int manhattan_distance(const auto& p1,const auto& p2);
  void possible_locations_on_row(int row,int search_range=0,bool verbose=false);
  int tuning_frequency(const Location& p);
  void show_nearest_beacon_distances();
  /*
  void std_for_each_3()
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

  void std_for_each_2();
  void std_for_each_1();
};

}

void day15_part1();
void day15_part2();

#endif // __DAY15_HPP
