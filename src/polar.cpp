#include "include/polar.h"
#include <iostream>
#include <memory>

Polar::Polar(options_t &options) : options(options)
{
    auto [port, path] = options;

    this->meta = std::make_shared<meta_t>();
    this->meta->path = options.path;
    this->meta->is_dir = false;

    std::cout << "\x1B[2J\x1B[H";
    std::cout << path << " :: " << port << std::endl;
}

void Polar::serve(void)
{
    std::cerr << "\nto be implemented" << std::endl;
}

Polar::~Polar()
{
    std::cout << "\nbye bye :)" << std::endl;
}
