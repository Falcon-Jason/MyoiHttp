//
// Created by jason on 2021/4/20.
//

#include "echo.h"

using namespace network;
using namespace std;

int main() {
    TcpConnection conn{"127.0.0.1", PORT};
    BufferedIo &connSocket = conn.io();
    string line{};

    fmt::print("Created Socket: {0}.\n", ConnectionInfo(conn));

    while (getline(cin, line)) {
        connSocket.nwrite(line.c_str(), line.size());
        connSocket.nwrite("\n", 1);

        char echoBuffer[BUFFER_SIZE];
        connSocket.readline(echoBuffer, BUFFER_SIZE);
        fmt::print("server: {}", echoBuffer);
    }
}