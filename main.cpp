#include <filesystem>
#include <iostream>
#include <string>
#include "polar.h"

int main(int argc, char **argv)
{
    std::string VERSION = "0.0.3-alpha";

    if (argc < 2) {
        std::cout << "Usage: polar [file/dir] --port [port]" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "--help") {
        std::string message = VERSION + " :: ./polar [file/dir] --port port";
        std::cout << message << std::endl;
        return 0;
    }

    options_t options = {.port = 8080, .path = argv[1]};

    if (std::filesystem::is_directory(std::filesystem::path(options.path))) {
        std::cerr << "directories are not supported yet :(" << std::endl;
        return 1;
    }

    Polar polar = Polar(options);
    polar.serve();

    return 0;
}
