#include "city.h"
#include "utils.h"
#include <utility>
#include <unistd.h>

City::City(int id, std::string name, size_t capacity) {
    this->capacity = capacity;
    this->id = id;
    this->name = std::move(name);
}
//Gets train from railway and move it to city if there is place (number of trains in city<capacity).
bool City::enter_city(std::shared_ptr<Railway> railway, unsigned int train_id) {
    enter_mutex.lock();
    railway->mut->lock();
    if(railway->train == nullptr) {
        railway->mut->unlock();
        enter_mutex.unlock();
        std::cout<<"Entered city: " << this->id << " by train: " << train_id << '\n';
        return std::any_of(this->trains.begin(), this->trains.end(), [&train_id](auto& tr) {return tr != nullptr && tr->id == train_id;});
    }
    if(this->trains.size() < capacity){
        std::cout<<"Enter city: " << this->id << " by train: " << train_id << '\n';
        this->trains.emplace_back(std::move(railway->train));
        railway->mut->unlock();
        enter_mutex.unlock();
        return true;
    } else {
        railway->mut->unlock();
        enter_mutex.unlock();
        return false;
    }
}


City::City(City &&other) noexcept {
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

bool City::leave_city(ITrain* train, std::shared_ptr<Railway> railway) {
    enter_mutex.lock();
    railway->mut->lock();
    if (!railway->occupied()) {
        for (auto tr = trains.begin(); tr != this->trains.end(); tr++) {
            if (*tr != nullptr && (*tr)->id == train->id) {
                railway->train = std::move(*tr);
                trains.erase(tr);
                railway->mut->unlock();
                enter_mutex.unlock();
                return true;
            }
        }
    } else {
        if (railway->can_swap(this->id)) {
            for (auto tr = trains.begin(); tr != this->trains.end(); tr++) {
                if (*tr != nullptr && (*tr)->id == train->id) {
//                for(auto rail = railways.begin(); rail != this->railways.end(); rail++) {
//                    if ((*rail)->train != nullptr && (*rail)->train->id == railway->train->id) {
                    railway->train->idle = false;
                    auto tmp = std::move(*tr);
                    trains.push_back(std::move(railway->train));
                    railway->train = std::move(tmp);
                    break;
//                std::swap(railway->train, *(tr));
//                std::atomic_store(&railway->train, *tr);
//                        auto temp = std::move((*rail)->train);
//                        (*rail)->train = std::move(*tr);
//                        (*tr) = std::move(temp);
//                        std::cout << "Swapped: " + std::to_string(railway->train->id) + " with: " +
//                                     std::to_string((*tr)->id) + " \n";
                    }
                }
            erase_if(trains, [](auto x) { return x == nullptr; });
            railway->mut->unlock();
            enter_mutex.unlock();
            return true;
//                }
//            }
        }
    }
    railway->mut->unlock();
    enter_mutex.unlock();
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
bool City::has_train(int train_id) {
    return std::ranges::any_of(trains, [train_id](std::shared_ptr<ITrain>& x){return x->id == train_id;});
}

unsigned int City::draw_trains(unsigned int x, unsigned int y, sf::Sprite sprite, sf::Text text, sf::RenderWindow& window) {
    enter_mutex.lock();
    for(int i = 0; i < trains.size(); i++) {
        if(trains[i]!= nullptr) {
            text.setPosition(x + BLOCK_SIZE + i * 6 * BLOCK_SIZE, y);
            text.setString(
                    "Train: " + std::to_string(trains[i]->id) + " => " + std::to_string(trains[i]->source_i) + " -> " +
                    std::to_string(trains[i]->destination));
            window.draw(text);
            sprite.setPosition(x + i * 6 * BLOCK_SIZE, y);
            window.draw(sprite);
        }
    }
    enter_mutex.unlock();
    return 0;
}

unsigned int City::draw_railways(unsigned int x, unsigned int y, sf::Sprite sprite, sf::Text text, sf::RenderWindow &window) {
    enter_mutex.lock();
    for(int i = 0; i < railways.size(); i++) {
        railways.at(i)->draw(x, y + 2*i * BLOCK_SIZE, sprite, text, window);
    }
    enter_mutex.unlock();
    return 2*BLOCK_SIZE*railways.size();
}
