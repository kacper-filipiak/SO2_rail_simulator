//
// Created by Kacper Filipiak Private on 12/04/2024.
//

#ifndef SO2_RAIL_SIMULATOR_ITRAIN_H
#define SO2_RAIL_SIMULATOR_ITRAIN_H

#include <string>
#include <thread>

class ITrain {
public:
    virtual std::unique_ptr<std::thread> departure() = 0;
    virtual ~ITrain() {};
    int id;
    unsigned int destination;
    unsigned int source_i = 0;
    std::mutex mutex;

    bool is_locked(){if(mutex.try_lock()) {
            mutex.unlock();
            return true;
        }
        return false;
    }
    virtual bool is_idle() = 0;
};

#endif //SO2_RAIL_SIMULATOR_ITRAIN_H
