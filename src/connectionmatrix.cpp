//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#include "connectionmatrix.h"

//Creates an empty neighbour matrix representing a graph with number of vertices equal to size
ConnectionMatrix::ConnectionMatrix(size_t size, std::unique_ptr<std::vector<City> > cities) {
    this->size = size;
    this->cities = std::move(cities);
    this->graph = new std::vector<Railway> *[this->size];
    for (auto i = 0; i < this->size; i++) {
        this->graph[i] = new std::vector<Railway>[this->size];
        for (auto j = 0; j < this->size; j++) {
            this->graph[i][j] = std::vector<Railway>();
        }
    }
}

//Avoids memory leak
ConnectionMatrix::~ConnectionMatrix() {
    for (auto i = 0; i < this->size; i++) {
        delete[] this->graph[i];
    }
    delete[] this->graph;
}

void ConnectionMatrix::addRailway(unsigned int a, unsigned int b, Railway railway) {
    this->graph[a][b].push_back(railway);
}
