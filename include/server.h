#include <string>

#ifndef __SERVER_H__
    #define __SERVER_H__

class Server {
  private:
    int server_port;
    int server_socket;
    void handler(int client_socket);

  public:
    Server(int port);
    bool start(void) noexcept(false);
    virtual std::string build_request(void) noexcept = 0;
    virtual ~Server() = 0;
};

#endif
