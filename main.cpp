//
// Created by Kacper Filipiak Private on 11/04/2024.
//

#include <iostream>
#include <memory>
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
#include <ranges>

int main(int argc, char** argv){
    if (__cplusplus == 202101L) std::cout << "C++23";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 199711L) std::cout << "C++98";
    else std::cout << "pre-standard C++." << __cplusplus;
    std::cout << "\n";
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


    auto railways_filename = result["railways"].as<std::string >();
    auto railways = std::vector<std::shared_ptr<Railway> >();
    std::ifstream railways_csv(railways_filename);
    for(std::string line; std::getline(railways_csv, line);) {
        std::istringstream iss(line);
        int a, b;
        unsigned int cost;
        iss>>a>>b>>cost;
        Railway railway(a, b, cost);
        railways.push_back(std::make_shared<Railway>(railway));
    }

    auto cities_filename = result["cities"].as<std::string >();

    std::ifstream cities_csv(cities_filename);
    std::shared_ptr<std::vector<City> > cities = std::make_shared<std::vector<City> >( );
    int id = 0;
    for(std::string line; std::getline(cities_csv, line); id++) {
        std::istringstream iss(line);
        std::string city_name;
        size_t capacity;
        iss >> city_name >> capacity;
        auto connected_rails = std::vector<std::shared_ptr<Railway> >();
        for(const auto&  rail : railways | std::ranges::views::filter([id](const std::shared_ptr<Railway>& rw){ return rw->is_connected_to(id); })) {
            connected_rails.push_back(rail);
        }
        City city = City(id, city_name, capacity, std::move(connected_rails));
        cities->push_back(std::move(city));
    }

    std::cout<<cities->size()<<'\n';

    auto trains_filename = result["trains"].as<std::string >();

    std::ifstream trains_csv(trains_filename);
    std::vector<std::shared_ptr<Train> > trains = std::vector<std::shared_ptr<Train> >();
    for(std::string line; std::getline(trains_csv, line);) {
        std::istringstream iss(line);
        int train_id;
        unsigned int start_city;
        iss >> train_id >> start_city;
        auto schedule = std::vector<int>();
        for(int stop; !(iss>>stop);){
            schedule.push_back(stop);
        }

        std::unique_ptr<Train> train(new Train(train_id, schedule, cities));
        train->departure();
        trains.push_back(std::move(train));
    }

    auto trains_threads = std::vector<std::thread>();
    for (auto& train : trains) {
        std::cout<<"Starting: "<<train->id<<'\n';
        train->get_starting_city()->add_train_to_city(train);
        trains_threads.push_back(train->departure());
    }
    for(auto& thread : trains_threads) {
        thread.join();
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

