#include <map>
#include <string>

#ifndef __MIME_H__
    #define __MIME_H__

class Mime {
  private:
    std::map<std::string, std::string> mime_types;

  public:
    Mime(void);
    std::string get_mime(std::string &path);
};
#endif
