#include "train.h"

#include <utility>

Train::Train(int id, std::vector<int> schedule, std::shared_ptr<std::vector<City> > cities) {
    this->id = id;
    this->schedule = std::move(schedule);
    this->cities = std::move(cities);
}

std::thread Train::departure() {
    return std::thread( [this] {
        this->travelling();
    } );
}

void Train::travelling() {
    int source = this->schedule.back();
    while (true) {
        for(auto destination : this->schedule) {
            auto& source_city = this->cities->at(source);
            auto& dest_city = this->cities->at(destination);
            auto rails_to_dest = source_city.getRailwaysConnectedTo(dest_city);
            bool leaved_city = false;
            while (!leaved_city) {
                for (auto &rail: *rails_to_dest) {
                    if(source_city.leave_city(this, rail)){
                        std::cout<<"Train " << this->id <<" departured from " << source_city <<" using " << rail << " rail\n";
                        //Train is driving dependent on distance
                        std::this_thread::sleep_for(std::chrono::milliseconds(rail->cost));
                        leaved_city = true;
                    }
                }
            }
            //Here train is on railway and it is near to dest time
            auto rail = source_city.getRailwayWithTrain(this->id);
            if(rail != nullptr){
                //Try to enter the city till success
                while(dest_city.enter_city(rail));
                std::cout<<"Train " << this->id <<" arrived to " << dest_city <<" using " << rail << " rail\n";
                source = destination;
            }
        }
        std::cout << "travelling " << id << "!!!\n";
    }
}
