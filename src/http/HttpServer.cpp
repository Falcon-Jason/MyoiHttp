//
// Created by jason on 2021/4/20.
//

#include "core/Error.h"
#include "core/TcpConnection.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "http/HttpServer.h"

#include <fmt/format.h>
#include <string>
#include <map>
#include <unistd.h>

using std::thread;
using std::string;
using fmt::print;

namespace network {
    HttpServer::HttpServer(const char *ip, int port, const char *baseDir)
            : baseDir{baseDir},
              listener{ip, port},
              selectSet{STDIN_FILENO, listener.fd()},
              address{listener.address()},
              end{false},
              retCode{0} {
        if(this->baseDir.back() == '/') {
            this->baseDir.pop_back();
        }
    }

    int HttpServer::exec() {
        print("Server is Running at {}:{}\n", address.ip(), address.port());
        for (;!end;) {
            auto readySet = selectSet.select();

            if (readySet.contains(listener.fd())) {
                thread t{HttpServer::HandleClient, baseDir, listener.accept()};
                t.detach();
            }

            if (readySet.contains(STDIN_FILENO)) {
                HandleConsole(*this);
            }
        }
        return 0;
    }

    void HttpServer::HandleClient(const std::string &baseDir, TcpConnection *conn) {
        BufferedIo &socket = conn->io();
        HttpRequest request{};
        HttpResponse response{};

        request.parse(socket);

        auto filename = baseDir + request.path;
        if (filename.back() == '/') {
            filename.append("index.html");
        }

        print("{} is requesting {}\n", conn->peerAddress().ip(), filename);
        response.setContentFile(filename.c_str());
        string out = response.toString();
        socket.nwrite(out.c_str(), out.size());
        delete conn;
    }

    void HttpServer::HandleConsole(HttpServer &server) {
        char buffer[BUFFER_SIZE];
        auto retCode = ::read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (retCode > 0) {
            print("console: {0}", buffer);
        } else if (retCode == 0) {
            print(stdout, "Exit Success.\n");
            server.end = true;
            server.retCode = EXIT_SUCCESS;
        } else if (errno != EINTR) {
            print(stderr, "EchoServer: {}.\n", strerror(errno));
            print(stdout, "Exit Failed.\n");
            server.end = true;
            server.retCode = EXIT_FAILURE;
        }
    }
}