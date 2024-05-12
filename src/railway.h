//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#ifndef SO2_RAIL_SIMULATOR_RAILWAY_H
#define SO2_RAIL_SIMULATOR_RAILWAY_H
#include <memory>
#include "itrain.h"
#include <ostream>
#include <SFML/Graphics.hpp>

class Railway {
public:
    unsigned int cost;
    unsigned int cities[2];
    //Shouldn't copy move ptr instead
    std::shared_ptr<ITrain> train;
    std::shared_ptr<std::mutex> mut = std::make_shared<std::mutex>();
    explicit Railway(unsigned int city1, unsigned int city2, unsigned int cost);
    Railway(Railway&& other) noexcept ;
    ~Railway();
    Railway(const Railway&) = default;
    bool is_connected_to(unsigned int city);
    bool has_train(int train);
    bool occupied() const;
    bool can_swap(unsigned int city_id) const;
    void draw(unsigned int x, unsigned int y, sf::Sprite sprite, sf::Text text, sf::RenderWindow &window);

    bool is_locked(){if(mut->try_lock()) {
            mut->unlock();
            return true;
        }
        return false;
    }

private:
};

#endif //SO2_RAIL_SIMULATOR_RAILWAY_H
