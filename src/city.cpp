#include "city.h"

#include <utility>

City::City(int id, std::string name, size_t capacity) {
    this->capacity = capacity;
    this->id = id;
    this->name = std::move(name);
}
//Gets train from railway and move it to city if there is place (number of trains in city<capacity).
bool City::enter_city(std::shared_ptr<Railway> railway) {
    if(railway->train == nullptr) {
        return false;
    }
    //Add mutex here
    //Analyze case when there is last place (risk of deadlock). Maybe swap with one of trains in city
    if(this->trains.size() < capacity){
        this->trains.emplace_back(std::move(railway->train));
        return true;
    } else {
        return false;
    }
}

City::City(City &&other) {
    this->id = other.id;
    this->name = other.name;
    this->capacity = other.capacity;
    this->trains = std::move(other.trains);
}

std::shared_ptr<Railway> City::getRailwayWithTrain(const int train_id) {
    for (const auto &rail: this->railways | std::ranges::views::filter(
            [train_id](const std::shared_ptr<Railway> &rw) { return rw->has_train(train_id); })) {
        return rail;
    }
    return nullptr;
}

std::unique_ptr<std::vector<std::shared_ptr<Railway> > > City::getRailwaysConnectedTo(const City &dest_city) {
    auto dest_id = dest_city.id;
    auto connected_rails = std::make_unique<std::vector<std::shared_ptr<Railway> > >();
    for (const auto &rail: this->railways | std::ranges::views::filter(
            [dest_id](const std::shared_ptr<Railway> &rw) { return rw->is_connected_to(dest_id); })) {
        connected_rails->push_back(rail);
    }
    return connected_rails;
}

bool City::leave_city(ITrain *train, const std::shared_ptr<Railway>& railway) {
    if(!railway->occupied()) {
        for(std::vector<std::shared_ptr<ITrain> >::iterator tr = trains.begin(); tr != this->trains.end(); tr++) {
            if((*tr)->id == train->id) {
               railway->train = *tr;
               trains.erase(tr);
               return true;
            }
        }
    }
    return false;
}

bool City::add_train_to_city(std::shared_ptr<ITrain> tr) {
    if(trains.size() < capacity) {
        std::cout<<"Added train "<<tr<<" to the city\n";
        this->trains.push_back(std::move(tr));
        return true;
    } else {
        return false;
    }
}

void City::add_rail_to_city(std::shared_ptr<Railway> rw) {
    this->railways.push_back(rw);
}
