#ifndef MIME_H
#define MIME_H

#include <map>
#include <string>

class Mime {
  private:
    std::map<std::string, std::string> mime_types;

  public:
    Mime(void);
    std::string get_mime(std::string &path);
};
#endif
