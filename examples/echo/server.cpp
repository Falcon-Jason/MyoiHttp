//
// Created by jason on 2021/4/20.
//

#include "echo.h"

using namespace std;
using namespace network;

void HandleClient(TcpConnection *conn) {
    char buffer[BUFFER_SIZE];
    ssize_t length;
    fmt::print("Accepted Socket: {0}\n", ConnectionInfo(*conn));

    BufferedIo &socket = conn->io();
    while ((length = socket.readline(buffer, BUFFER_SIZE)) > 0) {
//        fmt::print("{0}.{1}: {2}", conn->peerAddress().ip(), conn->peerAddress().port(), buffer);
        fmt::print("{}", buffer);
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
    TcpListener server{"127.0.0.1", PORT};
    SelectSet readSet{STDIN_FILENO, server.fd()};

    for (;;) {
        auto readySet = readSet.select();

        if (readySet.contains(server.fd())) {
            thread t{HandleClient, server.accept()};
            t.detach();
        }

        if (readySet.contains(STDIN_FILENO)) {
            HandleConsole();
        }
    }
}