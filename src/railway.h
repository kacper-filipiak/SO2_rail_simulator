//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#ifndef SO2_RAIL_SIMULATOR_RAILWAY_H
#define SO2_RAIL_SIMULATOR_RAILWAY_H
#include <memory>
#include "train.h"

struct Railway {
    unsigned int cost;
    std::unique_ptr<Train> train;
    explicit Railway(unsigned int cost);
    Railway(Railway&& other);
    ~Railway();
private:
    Railway(const Railway& other);
};

#endif //SO2_RAIL_SIMULATOR_RAILWAY_H
