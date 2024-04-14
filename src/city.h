#ifndef SO2_RW_CITY_H
#define SO2_RW_CITY_H
#include "itrain.h"
#include "railway.h"
#include <ranges>

class City {
  public:
//    Position pos;
    City(int id, std::string name, size_t capacity, std::vector<std::shared_ptr<Railway> > railways);
    bool enter_city(Railway& railway);
    std::shared_ptr<Railway> getRailwayWithTrain(std::shared_ptr<ITrain> train);
//    bool leave_city(Train* train, Railway* railway);

    City(City&& other);
  private:
    City(const City&) = default;
    int id;
    std::string name;
    //List off trains that are currently in the city
    //Shouldn't copy move ptr instead
    std::vector<std::shared_ptr<ITrain> > trains;
    size_t capacity;
//    std::vector<std::shared_ptr<Railway> > railways;
    std::vector<std::shared_ptr<Railway> > railways;
};

#endif
