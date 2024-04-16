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
    explicit Railway(unsigned int city1, unsigned int city2, unsigned int cost);
    Railway(Railway&& other);
    ~Railway();
    Railway(const Railway&) = default;
    bool is_connected_to(unsigned int city);
    [[nodiscard]] bool has_train(int train) const;
    bool occupied();
    void draw(unsigned int x, unsigned int y, sf::Sprite sprite, sf::Text text, sf::RenderWindow &window);
    friend std::ostream& operator<< ( std::ostream& outs, const Railway& obj ) {
        return outs << "Railway: { " << "cities: " << obj.cities[0] <<" - " << obj.cities[1] << ", " << "cost: " << obj.cost <<", " << "train: " << obj.train->id <<"} \n";
    }

private:
};

#endif //SO2_RAIL_SIMULATOR_RAILWAY_H
