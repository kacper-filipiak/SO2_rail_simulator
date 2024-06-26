#ifndef SO2_RW_CITY_H
#define SO2_RW_CITY_H
#include "itrain.h"
#include "railway.h"
#include <ranges>
#include <iostream>
#include <SFML/Graphics.hpp>

class City {
  public:
    City(int id, std::string name, size_t capacity);
    bool enter_city(std::shared_ptr<Railway> railway, unsigned int train_id);
    std::shared_ptr<Railway> getRailwayWithTrain(int train_id);
    std::unique_ptr<std::vector<std::shared_ptr<Railway> > > getRailwaysConnectedTo(const City& dest_city);
    bool leave_city(ITrain* train, std::shared_ptr<Railway> railway);
    bool add_train_to_city(std::shared_ptr<ITrain> tr);
    void add_rail_to_city(std::shared_ptr<Railway> rw);
    unsigned int draw_trains(unsigned int x, unsigned int y, sf::Sprite sprite, sf::Text text, sf::RenderWindow& window);
    unsigned int draw_railways(unsigned int x, unsigned int y, sf::Sprite sprite, sf::Text text, sf::RenderWindow& window);
    bool has_train(int train_id);


    friend std::ostream& operator<< ( std::ostream& outs, const City& obj ) {
        return outs << "City: { "
        << "id: " << obj.id <<", "
                << "train_count: " << obj.trains.size() <<", "
                << "capacity: " << obj.capacity <<", "
                << "railways_count: " << obj.railways.size() <<"} \n";
    }
    City(City&& other) noexcept ;
    int id;
  private:
    std::string name;
    //List off trains that are currently in the city
    //Shouldn't copy move ptr instead
    std::vector<std::shared_ptr<ITrain> > trains;
    size_t capacity;
    std::vector<std::shared_ptr<Railway> > railways;
    std::mutex enter_mutex = std::mutex();

};

#endif
