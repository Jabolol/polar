#include <iostream>
#include <string>
#include "include/polar.h"

int main(int argc, char **argv)
{
    std::string VERSION = "0.0.1-alpha";

    if (argc < 2) {
        std::cout << "Usage: polar [file/dir] --port [port]" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "--help") {
        std::string message = VERSION + " :: ./polar [file/dir] --port port";
        std::cout << message << std::endl;
        return 0;
    }

    options_t options;
    options.port = 8080;
    options.path = argv[1];

    std::unique_ptr<Polar> polar = std::make_unique<Polar>(options);

    polar->serve();

    return 0;
}
