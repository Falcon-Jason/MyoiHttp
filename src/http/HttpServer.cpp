//
// Created by jason on 2021/4/20.
//

#include "core/Error.h"
#include "core/TcpConnection.h"
#include "core/TcpListener.h"
#include "core/SelectSet.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include <fmt/format.h>
#include <string>
#include <map>
#include <unistd.h>

using namespace std;
using namespace network;

class HttpServer {
private:
    constexpr static int BUFFER_SIZE = 1024;
    string baseDir;
    TcpListener listener;
    SelectSet selectSet;
    const Ipv4Address &address;

public:
    HttpServer(const char *ip, int port, const char *baseDir = ".")
            : baseDir{baseDir},
              listener{ip, port},
              selectSet{STDIN_FILENO, listener.fd()},
              address{listener.address()} {}

    int exec() {
        fmt::print("Server is Running at {}:{}\n", address.ip(), address.port());
        for (;;) {
            auto readySet = selectSet.select();

            if (readySet.contains(listener.fd())) {
                thread t{HttpServer::HandleClient, baseDir, listener.accept()};
                t.detach();
            }

            if (readySet.contains(STDIN_FILENO)) {
                HandleConsole();
            }
        }
    }

private:
    static void HandleClient(const string& baseDir, TcpConnection *conn) {
        BufferedIo &socket = conn->io();
        HttpRequest request{};
        HttpResponse response{};

        request.parse(socket);

        fmt::print(request.toString());

        auto filename = baseDir + request.path;
        if (filename.back() == '/') {
            filename.append("index.html");
        }

        response.setContentFile(filename.c_str());

        string out = response.toString();
        fmt::print(out);
        socket.nwrite(out.c_str(), out.size());

        delete conn;
    }

    static void HandleConsole() {
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
};

int main() {
    return HttpServer{"127.0.0.1", 0}.exec();
}