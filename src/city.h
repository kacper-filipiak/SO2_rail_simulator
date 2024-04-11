#ifndef SO2_RW_CITY_H
#define SO2_RW_CITY_H
#include "train.h"
#include "railway.h"

class City {
  public:
//    Position pos;
    City(int id, std::string name, size_t capacity);
    bool enter_city(Railway& railway);
//    bool leave_city(Train* train, Railway* railway);

    City(City&& other);
  private:
    City(const City&) = default;
    int id;
    std::string name;
    //List off trains that are currently in the city
    std::vector<std::unique_ptr<Train> > trains;
    size_t capacity;
};

#endif
