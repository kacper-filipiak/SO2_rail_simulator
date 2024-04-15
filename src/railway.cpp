//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#include "railway.h"
#include "utils.h"

Railway::Railway(unsigned int city1, unsigned int city2, unsigned int cost) {
    this->cost= cost;
    this->cities[0] = city1;
    this->cities[1] = city2;
    this->train=nullptr;
}

Railway::Railway(Railway &&other) {
    this->cost = other.cost;
    this->train = std::move(other.train);
}

Railway::~Railway() {
}

bool Railway::is_connected_to(unsigned int city) {
    return this->cities[0] == city || this->cities[1] == city;
}

bool Railway::has_train(int train_id) const {
    if(this->train!= nullptr) {
        return this->train->id == train_id;
    } else {
        return false;
    }
}

bool Railway::occupied() {
    return this->train!= nullptr;
}

void Railway::draw(unsigned int x, unsigned int y, sf::Sprite sprite, sf::Text text, sf::RenderWindow &window) {

    if(train != nullptr) {
        text.setPosition(x, y );
        text.setString(std::to_string(cities[0]) + " ========                  ======== " + std::to_string(cities[1]));
        window.draw(text);
        text.setPosition(x + 4 * BLOCK_SIZE, y);
        text.setString("Train: " + std::to_string(train->id));
        window.draw(text);
        sprite.setPosition(x + 3 * BLOCK_SIZE, y);
        window.draw(sprite);
    } else {
        text.setPosition(x, y );
        text.setString(std::to_string(cities[0]) + " ================================== " + std::to_string(cities[1]));
        window.draw(text);
    }
}


