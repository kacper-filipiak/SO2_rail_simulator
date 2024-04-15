#ifndef SO2_RW_CITY_H
#define SO2_RW_CITY_H
#include "itrain.h"
#include "railway.h"
#include <ranges>
#include <iostream>

class City {
  public:
//    Position pos;
    City(int id, std::string name, size_t capacity);
    bool enter_city(std::shared_ptr<Railway> railway);
    std::shared_ptr<Railway> getRailwayWithTrain(int train_id);
    std::unique_ptr<std::vector<std::shared_ptr<Railway> > > getRailwaysConnectedTo(const City& dest_city);
    bool leave_city(ITrain* train, const std::shared_ptr<Railway>& railway);
    bool add_train_to_city(std::shared_ptr<ITrain> tr);
    void add_rail_to_city(std::shared_ptr<Railway> rw);

    friend std::ostream& operator<< ( std::ostream& outs, const City& obj ) {
        return outs << "City: { "
        << "id: " << obj.id <<", "
                << "train_count: " << obj.trains.size() <<", "
                << "capacity: " << obj.capacity <<", "
                << "railways_count: " << obj.railways.size() <<"} \n";
    }
    City(City&& other);
    int id;
  private:
    City(const City&) = default;
    std::string name;
    //List off trains that are currently in the city
    //Shouldn't copy move ptr instead
    std::vector<std::shared_ptr<ITrain> > trains;
    size_t capacity;
//    std::vector<std::shared_ptr<Railway> > railways;
    std::vector<std::shared_ptr<Railway> > railways;
};

#endif
