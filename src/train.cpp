#include "train.h"

#include <utility>

Train::Train(std::string name, std::vector<int> schedule, std::shared_ptr<std::vector<City> > cities) {
    this->name = std::move(name);
    this->schedule = std::move(schedule);
    this->cities = cities;
}

std::thread Train::departure() {
    return std::thread( [this] {
        this->travelling();
    } );
}

void Train::travelling() {
    auto& source_city = this->cities->at(this->schedule.back());
    while (true) {
        for(auto destination : this->schedule) {
            source_city.getRailwayWithTrain(std::make_shared<ITrain>(this));

            auto& destination_city = this->cities->at(destination);

        }
        std::cout << "travelling " << name << "!!!\n";
    }
}
