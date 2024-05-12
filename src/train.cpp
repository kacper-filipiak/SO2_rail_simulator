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
    this->mut->lock();
    idle = false;
//    this->mut->unlock();
    int source = schedule.back();
    source_i = source;
    try {
        while (true) {
            for (auto _destination: schedule) {
//                mutex.lock();
                destination = _destination;
//                mutex.unlock();
                std::cout << "Waiting on station " << source << "\n";
                this->mut->unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                this->mut->lock();
                auto &source_city = cities->at(source);
                auto &dest_city = cities->at(destination);
                auto rails_to_dest = source_city.getRailwaysConnectedTo(dest_city);
                if (rails_to_dest == nullptr || rails_to_dest->empty()) {
                    std::cout << "No rails from " << source << " to destination " << destination << '\n';
                    return;
                }
                bool leaved_city = false;
                std::shared_ptr<Railway> railway;
                while (!leaved_city) {
                    if(source != source_city.id) std::cout << "Train " << id << " at " << dest_city << " with wrong source: " << source << "can't leave \n";//<< " using " << rail << " rail\n";
                    for(auto rail = rails_to_dest->begin(); rail != rails_to_dest->end(); rail++) {
                        if (source_city.leave_city(this, rail)) {
                            railway = *rail;
                            std::cout << "Train " << id << " departured from " << source_city << " using " << railway->cities[0] << "-=-" << railway->cities[1] << '\n'
                                      << " rail\n";
                            this->mut->unlock();
                            //Train is driving dependent on distance
                            std::this_thread::sleep_for(std::chrono::milliseconds((*rail)->cost * 100));
                            this->mut->lock();
                            leaved_city = true;
                        }
                    }
                }
                //Here train is on railway and it is near to dest time
                railway->mut->lock();
                std::cout << "Train " << id << " from rail with train " << (railway->train != nullptr ? std::to_string(railway->train->id) : "nullptr") << "\n";
                railway->mut->unlock();
                auto rail = source_city.getRailwayWithTrain(id);

                if (rail != nullptr) {
//                    this->mut->lock();
                    idle = true;
//                    this->mut->unlock();
                    //Try to enter the city till success
                    this->mut->unlock();
                    while (!dest_city.enter_city(rail, this->id));
                    this->mut->lock();
                    idle = false;
//                    this->mut->unlock();
                    std::cout << "Train " << id << " arrived to " << dest_city << '\n';//<< " using " << rail << " rail\n";
                    source = destination;
                    source_i = source;
                    if(source != dest_city.id) std::cout << "Train " << id << " at " << dest_city << " with wrong source: " << source << '\n';//<< " using " << rail << " rail\n";
                } else {
                    std::cout << "Train " << id << " gone missing!\n";
                    source = destination;
                    source_i = source;
                    if(source != dest_city.id) std::cout << "Train " << id << " at " << dest_city << " with wrong source: " << source << '\n';//<< " using " << rail << " rail\n";
                }
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

bool Train::is_idle() {
//    this->mut->lock();
        auto is_idle = idle;
//    this->mut->unlock();
    return is_idle;
}
