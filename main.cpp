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
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "src/city.h"
#include "src/railway.h"
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
            ("t,trains", "Trains csv filename", cxxopts::value<std::string>()->default_value("/Users/kacperfilipiakprivate/Projects/University/SO2_rail_simulator/trains.csv"))
            ("c,cities", "Cities csv filename", cxxopts::value<std::string>()->default_value("/Users/kacperfilipiakprivate/Projects/University/SO2_rail_simulator/cities.csv"))
            ("r,railways", "Railways csv filename", cxxopts::value<std::string>()->default_value("/Users/kacperfilipiakprivate/Projects/University/SO2_rail_simulator/railways.csv"))
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
        cities->push_back(City(id, city_name, capacity));
        auto connected_rails = std::vector<std::shared_ptr<Railway>>();
    }
    for(auto& city : *cities) {
        for (const auto &rail: railways) {
            if (rail->is_connected_to(city.id)) {
                city.add_rail_to_city(rail);
            }
        }
    }

    std::cout<<cities->size()<<'\n';

    auto trains_filename = result["trains"].as<std::string >();

    std::ifstream trains_csv;
    trains_csv.open(trains_filename);
    std::vector<std::shared_ptr<Train> > trains = std::vector<std::shared_ptr<Train> >();
    if(!trains_csv.is_open()) {
        throw std::ios_base::failure("Could not read file " + trains_filename);
    }
    for(std::string line; std::getline(trains_csv, line);) {
        std::istringstream iss(line);
        int train_id;
        iss >> train_id;
        auto schedule = std::vector<int>();
        int stop;
        std::cout<<train_id << " :stops: ";
        while(iss>>stop) {
            std::cout<< stop << " -> ";
            schedule.push_back(stop);
        }
        std::cout<<'\n';

        std::unique_ptr<Train> train(new Train(train_id, schedule, cities));
        trains.push_back(std::move(train));
    }

    auto trains_threads = std::vector<std::unique_ptr<std::thread>>();
    for (auto& train : trains) {
        std::cout<<"Starting: "<<train->id<<'\n';
        train->get_starting_city().add_train_to_city(train);
        trains_threads.push_back(std::move(train->departure()));
    }
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Texture city_texture;
        if (!city_texture.loadFromFile("res/city.png"))
        {
            std::cout<< "ERROR: Could not load city.png";
            break;
        }

        sf::Texture train_texture;
        if (!train_texture.loadFromFile("res/train.png"))
        {
            std::cout<< "ERROR: Could not load train.png";
            break;
        }

        window.clear();

        sf::Sprite city_sprite;
        sf::Sprite train_sprite;
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("res/Micro5Charted-Regular.ttf"))
        {
            std::cout<< "ERROR: Could not load ttf file";
            break;
        }
        text.setFillColor(sf::Color::White);
        text.setFont(font); // font is a sf::Font
        text.setCharacterSize(24); // in pixels, not points!

        train_sprite.setTexture(train_texture);
        city_sprite.setTexture(city_texture);
        int cursor_y = 0;
        for(int i = 0; i < cities->size(); i++)
        {

            text.setPosition(2 * BLOCK_SIZE, cursor_y + 2 * i * BLOCK_SIZE);
            text.setString("City: " + std::to_string(i));
            window.draw(text);
            city_sprite.setPosition(0, cursor_y + 2 * i * BLOCK_SIZE);
            window.draw(city_sprite);
            cities->at(i).draw_trains(BLOCK_SIZE * 4, cursor_y + 2 * i * BLOCK_SIZE, train_sprite, text, window);
            cursor_y += cities->at(i).draw_railways(BLOCK_SIZE * 2, cursor_y + 2 * i * BLOCK_SIZE + BLOCK_SIZE, train_sprite, text, window);
        }

        window.display();
    }

    for(auto& thread : trains_threads) {
        thread->join();
    }
    return 0;
}

