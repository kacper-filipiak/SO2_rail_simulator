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
    //Shouldn't copy move ptr instead
    std::shared_ptr<ITrain> train;
    explicit Railway(unsigned int city1, unsigned int city2, unsigned int cost);
    Railway(Railway&& other);
    ~Railway();
    Railway(const Railway&) = default;
    bool is_connected_to(unsigned int city);
    bool has_train(const std::shared_ptr<ITrain>& train) const;
private:
};

#endif //SO2_RAIL_SIMULATOR_RAILWAY_H
