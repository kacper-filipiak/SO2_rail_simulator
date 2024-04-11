#include "train.h"

Train::Train(std::string name, std::vector<int> schedule, std::weak_ptr<ConnectionMatrix> connectionMatrix) {
    this->name = name;
    this->schedule = schedule;
    this->connectionMatrix = connectionMatrix;
}

std::thread Train::departure() {
    return std::thread( [this] {this->travelling();} );
}

void Train::travelling() {
    while (true) {
        std::cout << "travelling " << name << "!!!\n";
    }
}
