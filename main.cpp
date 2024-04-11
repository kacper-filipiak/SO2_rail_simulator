//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#include <iostream>
#include <thread>
#include "src/utils.h"
#include "include/cxxopts.hpp"
#include <SFML/Graphics.hpp>
#include "src/train.h"
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "src/city.h"
#include "src/railway.h"
#include "src/connectionmatrix.h"

int main(int argc, char** argv){
    // OPTIONS
    cxxopts::Options options("main_app", "Multithread, customizable animation of bees' lives");

    options.add_options()
            ("t,trains", "Trains csv filename", cxxopts::value<std::string>()->default_value("trains.csv"))
            ("c,cities", "Cities csv filename", cxxopts::value<std::string>()->default_value("cities.csv"))
            ("r,railways", "Railways csv filename", cxxopts::value<std::string>()->default_value("railways.csv"))
            ("h,help", "Print help")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    auto cities_filename = result["cities"].as<std::string >();

    std::ifstream cities_csv(cities_filename);
    std::unique_ptr<std::vector<City> > cities = std::unique_ptr<std::vector<City> >( new std::vector<City>() );
    int id = 0;
    for(std::string line; std::getline(cities_csv, line); id++) {
        std::istringstream iss(line);
        std::string city_name;
        size_t capacity;
        iss >> city_name >> capacity;
        City city = City(id, city_name, capacity);
        cities->push_back(std::move(city));
    }

    std::cout<<cities->size()<<'\n';

    std::shared_ptr<ConnectionMatrix> graph(new ConnectionMatrix(cities->size(), std::move(cities)));

    auto railways_filename = result["railways"].as<std::string >();

    std::ifstream railways_csv(railways_filename);
    for(std::string line; std::getline(railways_csv, line);) {
        std::istringstream iss(line);
        int a, b;
        unsigned int cost;
        iss>>a>>b>>cost;
        Railway railway(cost);
        graph->addRailway(a, b, std::move(railway));
    }



    auto trains_filename = result["trains"].as<std::string >();

    std::ifstream trains_csv(trains_filename);
    std::vector<std::unique_ptr<Train> > trains = std::vector<std::unique_ptr<Train> >();
    for(std::string line; std::getline(trains_csv, line);) {
        std::istringstream iss(line);
        std::string train_name;
        unsigned int start_city;
        iss >> train_name >> start_city;
        auto schedule = std::vector<int>();
        for(int stop; !(iss>>stop);){
            schedule.push_back(stop);
        }

        std::unique_ptr<Train> train(new Train(train_name, schedule, graph));
        train->departure();
        trains.push_back(std::move(train));
    }

    for (auto& train : trains) {
        std::cout<<train->name<<'\n';
    }
//    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        sf::Texture grass_texture;
//        if (!grass_texture.loadFromFile("res/grass.png"))
//        {
//            std::cout<< "ERROR: Could not load grass_texture grass.png";
//            break;
//        }
//
//        window.clear();
//
//        sf::Sprite grass_sprite;
//        grass_sprite.setTexture(grass_texture);
//
//        for(int y = 0; y < NUMBER_OF_BLOCKS; y++)
//            for(int i = 0; i < NUMBER_OF_BLOCKS; i++)
//            {
//                grass_sprite.setPosition(i * BLOCK_SIZE, y * BLOCK_SIZE);
//                window.draw(grass_sprite);
//            }
//
//
//        sf::Texture bee_texture;
//        if (!bee_texture.loadFromFile("res/bee.png"))
//        {
//            break;
//        }
//
//        sf::Sprite bee_sprite;
//        bee_sprite.setTexture(bee_texture);
//        for(int i = 0; i < bees_count; i++)
//        {
//            bee_sprite.setPosition(bees[i].pos.x * BLOCK_SIZE, bees[i].pos.y * BLOCK_SIZE);
//            window.draw(bee_sprite);
//        }
//
//        window.display();
//    }

    while (true);

}

