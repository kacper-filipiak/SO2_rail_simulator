#ifndef SO2_RW_TRAIN_H
#define SO2_RW_TRAIN_H

#include <string>
#include <thread>
#include <iostream>
#include "itrain.h"
#include "connectionmatrix.h"
#include <chrono>

//Trains should have current position (Railway or City with common interface extracted to omit circular dependency)
class Train : public ITrain {
public:
    explicit Train(int id, std::vector<int> schedule, std::shared_ptr<std::vector<City > > cities);
    std::unique_ptr<std::thread> departure() override;
    City& get_starting_city();
    ~Train() override = default;
private:
    std::vector<int> schedule;
    std::shared_ptr<std::vector<City > > cities;
    void travelling();
};
#endif
