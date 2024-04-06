#include <iostream>
#include <thread>
#include "include/cxxopts.hpp"

int main(int argc, char** argv){
    // OPTIONS
    cxxopts::Options options("main_app", "Multithread, customizable animation of bees' lives");

    options.add_options()
            ("b,bees", "Number of bees", cxxopts::value<size_t>()->default_value("2"))
            ("f,flowers", "Number of flowers", cxxopts::value<size_t>()->default_value("5"))
            ("H,hives", "Number of hives", cxxopts::value<size_t>()->default_value("2"))
            ("k,beekeepers", "Number of beekeepers", cxxopts::value<size_t>()->default_value("1"))
            ("p,pollen", "Pollen refresh rate [s]", cxxopts::value<size_t>()->default_value("5"))
            ("c, capacity", "Hives capacity", cxxopts::value<size_t>()->default_value("3"))
            ("w, work", "Bee work duration", cxxopts::value<size_t>()->default_value("7"))
            ("h,help", "Print help")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
}
