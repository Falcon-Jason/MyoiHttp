//
// Created by jason on 16/6/21.
//

#include "server/HttpServer.h"

#include <memory>


namespace myoi {
    bool HttpServer::init() {
        bool success;
        success = epoll.init();
        if (!success) {
            log.error("Epoll Initialize Failed");
            return false;
        }

        success = listener.listen(address);
        if (!success) {
            log.error("Bind or Listen Failed");
            return false;
        }

        Ipv4Address listenerAddress = listener.hostAddress();
        log.info("Listening to {}:{}", listenerAddress.address(), listenerAddress.port());

        epoll.addEvent(&listener);
        terminate = 0;
        return true;
    }

    void HttpServer::term() {
        terminate = 1;
    }

    int HttpServer::exec() {
        if (!init()) { return EXIT_FAILURE; }

        log.info("Initialization Finished");

        while (!terminate) {
            auto socket = epoll.wait();
            if (socket == nullptr || !socket->isOpen()) { continue; }

            Ipv4Address connAddr = socket->hostAddress();
            log.info("Connected to {}:{}", connAddr.address(), connAddr.port());

            switch (socket->type()) {
                case SocketType::LISTENER:
                    handleListener(socket);
                    break;
                case SocketType::CONNECTION:
                    log.info("Handling {}:{}", connAddr.address(), connAddr.port());
                    handleConnection(socket);
                    break;
                case SocketType::INVALID_TYPE:
                    log.error("Epoll got an invalid connection {}", socket->index());
                    break;
            }
        }

        controller.exit();
        parsers.clear();
        return EXIT_SUCCESS;
    }

    void HttpServer::handleListener(TcpSocket *socket) {
        auto newConn = socket->accept();
        addConnection(newConn);
//        epoll.addEvent(socket);
    }

    void HttpServer::handleConnection(TcpSocket *socket) {
        auto callback = [this](TcpSocket *socket, bool keepAlive) {
            if (keepAlive) {
                epoll.resetEvent(socket);
            } else {
                removeConnection(socket);
            }
        };
        return controller.handleConnection(socket, parsers.at(socket->index()).get(), callback);
    }

    void HttpServer::addConnection(const TcpSocket &socket) {
        parsers[socket.index()] = std::make_unique<HttpRequestParser>();
        connections[socket.index()] =std::make_unique<TcpSocket>(socket);
        epoll.addEvent(connections[socket.index()].get());
    }

    void HttpServer::removeConnection(TcpSocket *socket) {
        log.info("Closed Connection to {}", socket->hostAddress().toString());
        socket->close();
        if (parsers.count(socket->index())) { parsers.erase(socket->index()); }
        if (connections.count(socket->index())) { connections.erase(socket->index()); }

        epoll.removeEvent(socket);


    }
}
