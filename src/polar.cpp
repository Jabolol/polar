#include "polar.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

Polar::Polar(options_t &options) : Server(options.port), options(options)
{
    auto [port, path] = options;
    std::string CLEAR_SEQ = "\x1B[2J\x1B[H";

    std::cout << CLEAR_SEQ;
    std::cout << port << " :: " << path + "\n" << std::endl;
}

std::string Polar::get_file_content(void)
{
    auto [_, path] = options;
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

std::string Polar::build_request() noexcept
{
    std::string content = get_file_content();
    std::string type = mime.get_mime(options.path);

    return "HTTP/1.1 200 OK\r\nContent-Length:"
        + std::to_string(content.length()) + "\r\nContent-Type: " + type
        + "\r\n\r\n" + content;
}

void Polar::serve(void)
{
    try {
        start();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}
