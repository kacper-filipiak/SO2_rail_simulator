#include "city.h"

City::City(int id, std::string name, size_t capacity, std::vector<std::shared_ptr<Railway> > railways) {
    this->capacity = capacity;
    this->id = id;
    this->name = name;
    this->railways = railways;
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
        railway->train = nullptr;
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
    return std::move(connected_rails);
}

bool City::leave_city(ITrain *train, const std::shared_ptr<Railway>& railway) {
    if(!railway->occupied()) {
        for(auto& tr : this->trains) {
            if(tr->id == train->id) {
               railway->train.swap(tr);
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
