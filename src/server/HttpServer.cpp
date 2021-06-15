//
// Created by jason on 10/6/21.
//

#include "server/HttpServer.h"
#include "server/HttpRequestHandler.h"
#include <unistd.h>
#include <fmt/format.h>
#include <cassert>
#include <thread>
#include <iostream>

namespace myoi {
    using std::thread;
    int HttpServer::exec() {
        init();

        while (terminate == 0) {
            auto event = asio.getEvent();
            if (event == nullptr || event.type() == SocketType::INVALID_TYPE) { continue; }

            if (event.type() == SocketType::CONNECTION) {
                event.buffer()[event.bytesRead()] = '\0';
                thread th{&HttpServer::HandleClient, this, &connections[event.socket().index()]};
                th.detach();
            } else if (event.type() == SocketType::LISTENER) {
                HandleNewConnection();
            } else {
                fmt::print(stderr, "[ERROR] Invalid Connection Type\n");
            }
        }

        for(auto & connection : connections) {
            if (connection != nullptr) {
                asio.cancel(&connection->io);
                delete[] connection;
                connection = nullptr;
            }
        }

        return EXIT_SUCCESS;
    }

    void HttpServer::term() {
        terminate = 1;
    }

    void HttpServer::init() {
        bool success;

        success = asio.init();
        assert(success);
        success = listener.listen(hostAddress);
        assert(success);
        success = listener.hostAddress(hostAddress);
        assert(success);
        listenerBlock.initAsListener(listener);
        success = asio.submit(&listenerBlock);
        assert(success);

        logStartServer(listener);
    }

    void HttpServer::HandleClient(HttpConnection **pConnection) {
        auto &conn = *pConnection;
        auto &parser = conn->parser;
        HttpRequestHandler handler{};

        parser.parse(conn->ioBuffer);
        if (parser.open()) {
            asio.submit(&conn->io);
            return;
        }

        if (parser.failure()) {
            handler.initError(400);
        } else if (parser.success()) {
            handler.init(parser.request(), baseDir);
        }

        handler.writeTo(conn->io.socket());
        if (handler.hasDataToSend()) {
            handler.sendDataTo(conn->io.socket());
        }

        logCloseConnection(conn->io.socket());
        conn->io.socket().close();
        delete conn;
        *pConnection = nullptr;
    }

    void HttpServer::HandleNewConnection() {
        auto acceptor = listener.accept();
        if (!acceptor.isOpen()) { return; }
        logNewConnection(acceptor);

        int index = acceptor.index();
        assert(connections[index] == nullptr);
        auto newConn = connections[index] = new HttpConnection{};
        newConn->io.initAsConnection(acceptor, newConn->ioBuffer, BUFFER_SIZE);
        asio.submit(&newConn->io);
        asio.submit(&listenerBlock);
    }

    void HttpServer::logCloseConnection(const TcpSocket &socket) {
        Ipv4Address address{};
        socket.peerAddress(address);
        fmt::print(stdout, "[INFO] Closed Connection to {}:{}\n", address.address(), address.port());
    }

    void HttpServer::logNewConnection(const TcpSocket &socket) {
        Ipv4Address address{};
        socket.peerAddress(address);
        fmt::print(stdout, "[INFO] New Connection from {}:{}\n", address.address(), address.port());
    }

    void HttpServer::logStartServer(const TcpSocket &socket) {
        Ipv4Address address{};
        socket.hostAddress(address);
        fmt::print(stdout, "[INFO] Started server at localhost:{}\n", address.port());
    }

    HttpServer::~HttpServer() noexcept {
        for (auto & connection : connections) {
            if (connection != nullptr) {
                asio.cancel(&connection->io);
                delete connection;
                connection = nullptr;
            }
        }

        asio.destroy();
    }
}
