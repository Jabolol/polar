#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "signals.h"

class Server : public Signal {
  private:
    int server_port;
    int server_socket;
    static bool terminate_server;
    void handler(int client_socket);

  public:
    Server(int port);
    bool start(void);
    virtual std::string build_request(void) noexcept = 0;
    virtual ~Server() = 0;
};

#endif
