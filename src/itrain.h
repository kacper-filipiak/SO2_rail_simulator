//
// Created by Kacper Filipiak Private on 12/04/2024.
//

#ifndef SO2_RAIL_SIMULATOR_ITRAIN_H
#define SO2_RAIL_SIMULATOR_ITRAIN_H

#include <string>
#include <thread>

class ITrain {
public:
    virtual std::thread departure() = 0;
    virtual ~ITrain() {};
    int id;
};

#endif //SO2_RAIL_SIMULATOR_ITRAIN_H
