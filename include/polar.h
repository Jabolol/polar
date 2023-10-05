#include <memory>
#include <string>
#include "include/mime.h"

#ifndef __POLAR_H__
    #define __POLAR_H__

typedef struct {
    int port;
    std::string path;
} options_t;

typedef struct {
    bool is_dir;
    std::string path;
} meta_t;

class Polar {
  protected:
    Mime mime;
    options_t &options;
    std::shared_ptr<meta_t> meta;
    void serve_dir(void);
    void serve_file(void);

  public:
    Polar(options_t &options);
    void serve(void);
    ~Polar();
};

#endif
