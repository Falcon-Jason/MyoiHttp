//
// Created by jason on 2021/4/20.
//

#include "echo/echo.h"

using namespace std;
using namespace network;

void HandleClient(TcpConnection *conn) {
    char buffer[BUFFER_SIZE];
    ssize_t length;
    fmt::print("Accepted Socket: {0}\n", ConnectionInfo(*conn));

    BufferedIo &socket = conn->io();
    while ((length = socket.readline(buffer, BUFFER_SIZE)) > 0) {
        fmt::print("{0}.{1}: {2}", conn->peerAddress().ip(), conn->peerAddress().port(), buffer);
        socket.nwrite(buffer, length);
    }

    fmt::print("Closed Socket: {0}\n", ConnectionInfo(*conn));

    delete conn;
}

void HandleConsole() {
    char buffer[BUFFER_SIZE];
    auto retCode = ::read(STDIN_FILENO, buffer, BUFFER_SIZE);
    if (retCode > 0) {
        fmt::print("console: {0}", buffer);
    } else if (retCode == 0) {
        ::exit(EXIT_SUCCESS);
    } else if (errno != EINTR) {
        Error("EchoServer: %s.\n", strerror(errno));
    }
}

int main() {
    TcpServer server{"127.0.0.1", PORT};
    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(server.fd(), &read_set);

    for (;;) {
        fd_set ready_set = read_set;

        if (::select(server.fd() + 1, &ready_set, nullptr, nullptr, nullptr) < 0) {
            Error("EchoServer: select error: %s.\n", strerror(errno));
        }

        if (FD_ISSET(server.fd(), &ready_set)) {
            thread t{HandleClient, server.accept()};
            t.detach();
//            HandleClient(server.accept());
        }

        if (FD_ISSET(STDIN_FILENO, &ready_set)) {
            HandleConsole();
        }
    }
}