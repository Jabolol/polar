#include "request.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

Request::Request(const std::string& request)
{
    if (request.empty()) {
        return;
    }

    std::vector<std::string> lines = split(request, '\n');
    std::vector<std::string> first_line = split(lines[0], ' ');

    method = first_line[0];
    path = first_line[1];

    auto lower = [](std::string str) -> std::string {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    };

    for (unsigned int i = 1; i < lines.size(); i++) {
        if (lines[i].empty() || lines[i] == "\r") {
            break;
        }
        std::vector<std::string> header = split(lines[i], ':');
        headers[lower(header[0])] = header[1];
    }
}

std::vector<std::string> Request::split(const std::string &str, char delim)
{
    std::string token;
    std::stringstream ss(str);
    std::vector<std::string> parsed;

    while (std::getline(ss, token, delim)) {
        parsed.push_back(token);
    }
    return parsed;
}
