#ifndef __POLAR_H__
#define __POLAR_H__

#include <string>
#include "mime.h"
#include "server.h"

typedef struct {
    int port;
    std::string path;
} options_t;

typedef struct {
    bool is_dir;
    std::string path;
} meta_t;

class Polar : public Server {
  protected:
    Mime mime;
    std::unique_ptr<options_t> options;
    std::string get_file_content(void);
    void serve_dir(void);
    void serve_file(void);
    std::string build_request(void) noexcept;

  public:
    Polar(options_t &options);
    void serve(void);
    ~Polar() = default;
};

#endif
