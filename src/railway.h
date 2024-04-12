//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#ifndef SO2_RAIL_SIMULATOR_RAILWAY_H
#define SO2_RAIL_SIMULATOR_RAILWAY_H
#include <memory>
#include "itrain.h"

struct Railway {
    unsigned int cost;
    unsigned int cities[2];
    std::unique_ptr<ITrain> train;
    explicit Railway(unsigned int city1, unsigned int city2, unsigned int cost);
    Railway(Railway&& other);
    ~Railway();
private:
    Railway(const Railway& other);
};

#endif //SO2_RAIL_SIMULATOR_RAILWAY_H
