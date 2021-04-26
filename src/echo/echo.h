//
// Created by jason on 2021/4/20.
//

#ifndef NETWORK_ECHO_H
#define NETWORK_ECHO_H

#include "core/BufferedIo.h"
#include "core/TcpConnection.h"
#include "core/Error.h"
#include <fmt/format.h>
#include <string>
#include "core/TcpListener.h"
#include "core/TcpConnection.h"
#include <thread>
#include <memory>
#include <fmt/format.h>
#include "core/SelectSet.h"

std::string ConnectionInfo(const network::TcpConnection &conn) {
    return fmt::format("({0}:{1}, {2}:{3})",
                       conn.hostAddress().ip(),
                       conn.hostAddress().port(),
                       conn.peerAddress().ip(),
                       conn.peerAddress().port());
}

constexpr int PORT = 1234;
constexpr int BUFFER_SIZE = 65536;
#endif //NETWORK_ECHO_H
