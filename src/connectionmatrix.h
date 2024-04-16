//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#ifndef SO2_RAIL_SIMULATOR_CONNECTIONMATRIX_H
#define SO2_RAIL_SIMULATOR_CONNECTIONMATRIX_H
#include "railway.h"
#include "city.h"
#include <memory>

class ConnectionMatrix {
public:
    explicit ConnectionMatrix(size_t size, std::unique_ptr<std::vector<City> > cities);
    void addRailway(unsigned int a, unsigned int b, Railway railway);
    ~ConnectionMatrix();
private:
    std::vector<Railway>** graph;
    std::unique_ptr<std::vector<City> > cities;
    size_t size;
};


#endif //SO2_RAIL_SIMULATOR_CONNECTIONMATRIX_H
