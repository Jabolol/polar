#include <memory>
#include <string>
#include "include/mime.h"
#include "server.h"

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

class Polar : public Server {
  protected:
    Mime mime;
    options_t &options;
    std::shared_ptr<meta_t> meta;
    std::string get_file_content(void);
    void serve_dir(void);
    void serve_file(void);
    std::string build_request(void) noexcept override
    {
        std::string content = get_file_content();
        std::string type = mime.get_mime(options.path);

        return "HTTP/1.1 200 OK\r\nContent-Length:"
            + std::to_string(content.length()) + "\r\nContent-Type: " + type
            + "\r\n\r\n" + content;
    }

  public:
    Polar(options_t &options);
    void serve(void);
    ~Polar();
};

#endif
