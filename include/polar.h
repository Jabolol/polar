#ifndef __POLAR_H__
#define __POLAR_H__

#include <string>
#include "mime.h"
#include "server.h"

using options_t = struct {
    int port;
    std::string path;
};

using meta_t = struct {
    bool is_dir;
    std::string path;
};

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
