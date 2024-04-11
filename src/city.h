#ifndef SO2_RW_CITY_H
#define SO2_RW_CITY_H
#include "train.h"

class City {
  public:
//    Position pos;
    City(int id, std::string name, size_t capacity);
//    bool enter_city(Train* train, Railway* railway);
//    bool leave_city(Train* train, Railway* railway);

  private:
    int id;
    std::string name;
    //List off trains that are currently in the city
    std::vector<Train> trains;
    size_t capacity;
};

#endif
