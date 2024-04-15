#include "train.h"

#include <utility>

Train::Train(int id, std::vector<int> schedule, std::shared_ptr<std::vector<City> > cities) {
    this->id = id;
    this->schedule = std::move(schedule);
    this->cities = cities;
}

std::unique_ptr<std::thread> Train::departure() {
    return std::make_unique<std::thread>( std::thread( [this] {
        std::cout<<"Started journey of "<<this->id;
        travelling();
    } ));
}

void Train::travelling() {
    int source = schedule.back();
    try {
        while (true) {
            for (auto destination: schedule) {
                auto &source_city = cities->at(source);
                auto &dest_city = cities->at(destination);
                auto rails_to_dest = source_city.getRailwaysConnectedTo(dest_city);
                if (rails_to_dest == nullptr || rails_to_dest->empty()) {
                    std::cout << "No rails from " << source << " to destination " << destination << '\n';
                    return;
                }
                bool leaved_city = false;
                while (!leaved_city) {
                    for (auto &rail: *rails_to_dest) {
                        if (source_city.leave_city(this, rail)) {
                            std::cout << "Train " << id << " departured from " << source_city << " using " << rail
                                      << " rail\n";
                            //Train is driving dependent on distance
                            std::this_thread::sleep_for(std::chrono::milliseconds(rail->cost * 100));
                            leaved_city = true;
                        }
                    }
                }
                //Here train is on railway and it is near to dest time
                auto rail = source_city.getRailwayWithTrain(id);
                if (rail != nullptr) {
                    //Try to enter the city till success
                    while (!dest_city.enter_city(rail));
                    std::cout << "Train " << id << " arrived to " << dest_city ;//<< " using " << rail << " rail\n";
                    source = destination;
                } else {
                    std::cout << "Train " << id << " gone missing!\n";
                }
                std::cout << "Waiting on station " << id << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            std::cout << "travelling " << id << "!!!\n";
        }
    }catch (std::exception e) {
       std::cout<<e.what();
    }
}

City& Train::get_starting_city() {
    return cities->at(schedule.back());
}
