#include "city.h"

City::City(int id, std::string name, size_t capacity) {
    this->trains = std::vector<Train>();
    this->capacity = capacity;
    this->id = id;
    this->name = name;
}