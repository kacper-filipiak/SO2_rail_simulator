#ifndef SO2_RW_TRAIN_H
#define SO2_RW_TRAIN_H

#include <string>
#include <thread>
#include <iostream>
#include "itrain.h"
#include "connectionmatrix.h"

//Trains should have current position (Railway or City with common interface extracted to omit circular dependency)
class Train : public ITrain {
public:
    std::string name;
    explicit Train(std::string name, std::vector<int> schedule, std::weak_ptr<ConnectionMatrix> connectionMatrix);
    std::thread departure();
    ~Train() = default;
private:
    std::vector<int> schedule;
    void travelling();
    std::weak_ptr<ConnectionMatrix> connectionMatrix;
};

#endif
