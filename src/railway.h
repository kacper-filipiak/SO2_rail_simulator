//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#ifndef SO2_RAIL_SIMULATOR_RAILWAY_H
#define SO2_RAIL_SIMULATOR_RAILWAY_H
#include <memory>
#include "itrain.h"
#include <ostream>
#include <SFML/Graphics.hpp>

static const int COLOR_INC = 10;
static const int COLOR_DEC = 4;

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

    bool is_locked() const{if(mut->try_lock()) {
            mut->unlock();
            return true;
        }
        return false;
    }

    void bump_color(){
        if(color + COLOR_INC < 255){
            color += COLOR_INC;
        } else {
            color = 255;
        }
    }

    void reduce_color() {
        if(clock_div > 600) {
            clock_div=0;
            if (color - COLOR_DEC > 0) {
                color -= COLOR_DEC;
            } else {
                color = 0;
            }
        } else {
            clock_div ++;
        }
    }

private:
    int color = 0;
    int clock_div = 0;
};

#endif //SO2_RAIL_SIMULATOR_RAILWAY_H
