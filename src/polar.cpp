#include "include/polar.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

Polar::Polar(options_t &options) : Server(options.port), options(options)
{
    auto [port, path] = options;

    meta = std::make_shared<meta_t>();
    meta->path = options.path;
    meta->is_dir = false;

    std::cout << "\x1B[2J\x1B[H";
    std::cout << port << " :: " << path + "\n" << std::endl;
}

std::string Polar::get_file_content(void)
{
    std::string path = options.path;
    std::ifstream file(path);

    try {
        if (!file.is_open()) {
            throw std::runtime_error("could not open file");
        }
        std::string content((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
        file.close();
        return content;
    } catch (std::runtime_error &e) {
        return e.what();
    }
}

void Polar::serve(void)
{
    try {
        start();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

Polar::~Polar()
{
    std::cout << "\nbye bye :)" << std::endl;
}
