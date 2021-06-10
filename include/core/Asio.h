//
// Created by jason on 3/6/21.
//

#ifndef MYOIHTTP_ASIO_H
#define MYOIHTTP_ASIO_H

#include "TcpSocket.h"

#include <cassert>
#include <memory>
#include <libaio.h>

namespace myoi {
    class AsioBlock : private iocb {
    public:
        AsioBlock() : iocb{} {}
        ~AsioBlock() = default;

        [[nodiscard]] TcpSocket socket() const;
        [[nodiscard]] SocketType type() const;
        [[nodiscard]] size_t bufferSize() const;
        char *buffer() { assert(type() == SocketType::CONNECTION); return (char *)u.c.buf; }

        void initAsConnection(TcpSocket &socket, char *buffer, size_t size);
        void initAsListener(TcpSocket &socket);

        friend class Asio;
    };

    class AsioEvent {
    private:
        AsioBlock *io_{nullptr};
        size_t bytesRead_{0};

        explicit AsioEvent(const io_event& event);
        AsioEvent() = default;

    public:
        ~AsioEvent() = default;

        [[nodiscard]] size_t bytesRead() const { return bytesRead_; }
        [[nodiscard]] TcpSocket socket() const { return io_->socket(); }
        [[nodiscard]] SocketType type() const { return io_->type(); }
        [[nodiscard]] size_t bufferSize() const { return io_->bufferSize(); }
        [[nodiscard]] char *buffer() { return io_->buffer(); }

        bool operator==(nullptr_t null) const { return io_ == nullptr; }

        friend class Asio;
    };


    class Asio {
    public:
        io_context_t context{nullptr};

    public:
        Asio() = default;

        bool init();

        bool destroy() const;

        bool submit(AsioBlock *io) const;

        bool cancel(AsioBlock *io) const;

        [[nodiscard]] AsioEvent getEvent() const;
    };
}

#endif //MYOIHTTP_ASIO_H
