//
// Created by jason on 3/6/21.
//

#ifndef MYOIHTTP_ASIO_H
#define MYOIHTTP_ASIO_H

#include "TcpSocket.h"

#include <memory>
#include <libaio.h>

namespace myoi {
    class AsioEvent : private iocb{
    private:
        char *buffer_{nullptr};
        size_t byteRead_{0};
        SocketType type_{SocketType::INVALID_TYPE};

        AsioEvent() : iocb{} {}

    public:
        ~AsioEvent();
        [[nodiscard]] TcpSocket socket() const { return TcpSocket{aio_fildes, type_}; }
        [[nodiscard]] char *buffer() const { return buffer_; }
        [[nodiscard]] SocketType type() const { return type_; }
        [[nodiscard]] size_t byteRead() const { return byteRead_; };
        [[nodiscard]] size_t bufferSize() const;

        static AsioEvent *MakeRead(TcpSocket &connection, size_t size);
        static AsioEvent *MakePoll(TcpSocket &listener);

        friend class Asio;

    private:
        void clear();
    };


    class Asio {
    public:
        io_context_t context{nullptr};

    public:
        Asio() = default;

        bool init();

        bool submit(AsioEvent *io) const;

        [[nodiscard]] AsioEvent *getEvent() const;
    };
}

#endif //MYOIHTTP_ASIO_H
