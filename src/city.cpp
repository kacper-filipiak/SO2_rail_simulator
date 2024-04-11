#include "city.h"

City::City(int id, std::string name, size_t capacity) {
    this->capacity = capacity;
    this->id = id;
    this->name = name;
}
//Gets train from railway and move it to city if there is place (number of trains in city<capacity).
bool City::enter_city(Railway &railway) {
    if(railway.train == nullptr) {
        return false;
    }
    //Add mutex here
    //Analyze case when there is last place (risk of deadlock). Maybe swap with one of trains in city
    if(this->trains.size() < capacity){
        this->trains.emplace_back(std::move(railway.train));
        railway.train = nullptr;
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
