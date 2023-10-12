#include "server.h"
#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include "request.h"
#include "signals.h"

bool Server::terminate_server = false;

Server::Server(int port) : Signal(), server_port(port), server_socket(-1)
{
    auto handler = [](int sig) -> void {
        if (sig == SIGINT) {
            Server::terminate_server = true;
        }
    };
    register_signal(SIGINT, handler);
}

Server::~Server()
{
    if (server_socket != -1) {
        close(server_socket);
    }
}

void Server::handler(int client_socket)
{
    int len = 0;
    socklen_t len_size = sizeof len;
    getsockopt(client_socket, SOL_SOCKET, SO_RCVBUF, &len, &len_size);

    std::shared_ptr<char[]> buffer(new char[len + 1]);
    buffer[len] = '\0';
    recv(client_socket, buffer.get(), len, MSG_PEEK);

    Request request = Request(buffer.get());
    std::cout << request.method << " ==> " << request.path << std::endl;

    std::string response = build_request();
    send(client_socket, response.c_str(), response.length(), 0);
}

bool Server::start(void)
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        throw std::runtime_error(strerror(errno));
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);

    if (bind(server_socket, (struct sockaddr *) &server_addr,
            sizeof server_addr)
        == -1) {
        throw std::runtime_error(strerror(errno));
    }

    if (listen(server_socket, 5) == -1) {
        throw std::runtime_error(strerror(errno));
    }

    while (!Server::terminate_server) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof client_addr;
        int client_socket = accept(
            server_socket, (struct sockaddr *) &client_addr, &client_len);

        if (client_socket == -1) {
            continue;
        }
        handler(client_socket);
        close(client_socket);
    }

    close(server_socket);
    return true;
}
