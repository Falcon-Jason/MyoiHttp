//
// Created by jason on 26/4/21.
//

#include "http/HttpRequestParser.h"
#include "http/HttpRequestHandler.h"
#include "core/Ipv4Address.h"
#include "core/Asio.h"
#include <string>
#include <list>
#include <fmt/format.h>
#include <cassert>
#include <thread>
#include <unistd.h>

using namespace myoi;
TcpSocket listener{};
Asio asio{};

void HandleClient(TcpSocket socket);
void MakeConnection(TcpSocket socket);
void CloseConnection(TcpSocket socket);

int main(int argc, const char **argv) {
    using namespace myoi;
    asio.init();
    bool success = listener.listen(Ipv4Address{"127.0.0.1", 0});
    assert(success);

    Ipv4Address address;
    listener.hostAddress(address);
    fmt::print("{}\n", address.port());

    auto *listenerEvent = AsioEvent::MakePoll(listener);
    success = asio.submit(listenerEvent);
    assert(success);

    while(true) {
        AsioEvent *event = asio.getEvent();
        if (event == nullptr || event->type() == myoi::SocketType::INVALID_TYPE) {
            continue;
        }

        if (event->type() == myoi::SocketType::LISTENER) {
            auto newConn = listener.accept();
            assert(newConn.isOpen());
            MakeConnection(newConn);
            asio.submit(listenerEvent);
        } else if (event->type() == myoi::SocketType::CONNECTION) {
            auto socket = event->socket();
            HandleClient(socket);
        }
    }

    delete listenerEvent;
    listener.close();
}


AsioEvent *events[1024];
HttpRequestParser *parsers[1024];


void HandleClient(TcpSocket socket) {
    auto index = socket.index();
    auto &parser = parsers[index];
    auto &event = events[index];
    parser->parse(event->buffer());
    if (parser->open()) {
        asio.submit(event);
        return;
    }

    HttpRequestHandler handler{};
    if (parser->failure()) {
        handler.initError(400);
    } else if (parser->success()) {
        handler.init(parser->request());
    }

    handler.writeTo(socket);
    CloseConnection(socket);
}

void CloseConnection(TcpSocket socket) {
    Ipv4Address address{};
    socket.peerAddress(address);
    fmt::print("CloseConnection({})\n", address.port());

    int index = socket.index();

    delete parsers[index];
    delete events[index];
    events[index] = nullptr;
    socket.close();
}

void MakeConnection(TcpSocket socket) {
    Ipv4Address address{};
    socket.peerAddress(address);
    fmt::print("MakeConnection({})\n", address.port());

    int index = socket.index();

    events[index] = AsioEvent::MakeRead(socket, 1024);
    parsers[index] = new HttpRequestParser{};
    asio.submit(events[index]);
}