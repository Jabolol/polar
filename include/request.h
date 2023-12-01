#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <string>
#include <vector>
#include <unordered_map>

class Request {
  public:
    Request(const std::string& request);
    std::string path;
    std::string method;
    std::unordered_map<std::string, std::string> headers;
    ~Request() = default;

  private:
    std::vector<std::string> split(const std::string& str, char delim);
};

#endif
