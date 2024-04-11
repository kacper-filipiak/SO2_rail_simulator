#ifndef SO2_RW_TRAIN_H
#define SO2_RW_TRAIN_H

#include <string>

class Train {
public:
    std::string name;
    explicit Train(std::string name, std::vector<int> schedule);
private:
    std::vector<int> schedule;
};

#endif
