#include "server.h"
#include <atomic>
#include <csignal>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

std::atomic<bool> terminate_server(false);

void handle_signal(int signal)
{
    if (signal == SIGINT) {
        terminate_server.store(true);
    }
}

Server::Server(int port) : server_port(port), server_socket(-1)
{
    struct sigaction sigbreak;
    std::memset(&sigbreak, 0, sizeof sigbreak);
    sigbreak.sa_handler = handle_signal;

    if (sigaction(SIGINT, &sigbreak, NULL) != 0) {
        throw std::runtime_error("Error setting up signal handler");
    }
}

Server::~Server()
{
    if (server_socket != -1) {
        close(server_socket);
    }
}

void Server::handler(int client_socket)
{
    std::string response = build_request();
    send(client_socket, response.c_str(), response.length(), 0);
}

bool Server::start(void) noexcept(false)
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        throw std::runtime_error("Error creating socket");
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);

    if (bind(server_socket, (struct sockaddr *) &server_addr,
            sizeof(server_addr))
        == -1) {
        throw std::runtime_error("Error binding socket to port");
    }

    if (listen(server_socket, 5) == -1) {
        throw std::runtime_error("Error listening for connections");
    }

    while (!terminate_server.load()) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int clientSocket = accept(
            server_socket, (struct sockaddr *) &client_addr, &client_len);

        if (clientSocket == -1) {
            continue;
        }
        handler(clientSocket);
        close(clientSocket);
    }

    close(server_socket);
    return true;
}
