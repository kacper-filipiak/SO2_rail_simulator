//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#include "railway.h"

Railway::Railway(unsigned int cost) {
    this->cost= cost;
    this->train=nullptr;
}

Railway::Railway(Railway &&other) {
    this->cost = other.cost;
    this->train = std::move(other.train);
}

Railway::~Railway() {
}
