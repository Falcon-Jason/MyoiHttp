//
// Created by jason on 3/6/21.
//

#include "core/Asio.h"
#include <unistd.h>

namespace myoi {
    /*
     * Defined in <linux/aio_abi.h>.
     * Errors occurred when I included both
     * <libaio.h> and <linux/aio_abi.h>.
     * As a result, I have to copy these
     * definitions from <linux/aio_abi.h> here.
     */
    enum {
        IOCB_CMD_PREAD = 0,
        IOCB_CMD_PWRITE = 1,
        IOCB_CMD_FSYNC = 2,
        IOCB_CMD_FDSYNC = 3,
        IOCB_CMD_POLL = 5,
        IOCB_CMD_NOOP = 6,
        IOCB_CMD_PREADV = 7,
        IOCB_CMD_PWRITEV = 8,
    };

    size_t AsioBlock::bufferSize() const {
        if (type() != SocketType::CONNECTION) { return 0; }
        return u.c.nbytes;
    }

    SocketType AsioBlock::type() const {
        switch (aio_lio_opcode) {
            case IOCB_CMD_PREAD:
            case IOCB_CMD_PWRITE:
                return SocketType::CONNECTION;
            case IOCB_CMD_POLL:
                return SocketType::LISTENER;
            default:
                return SocketType::INVALID_TYPE;
        }
    }

    TcpSocket AsioBlock::socket() const {
        return TcpSocket{aio_fildes, type()};
    }

    void AsioBlock::initAsConnection(TcpSocket &socket, char *buffer, size_t size) {
        io_prep_pread(static_cast<iocb *>(this), socket.socket_, buffer, size, 0);
    }

    void AsioBlock::initAsListener(TcpSocket &socket) {
        io_prep_poll(static_cast<iocb *>(this), socket.socket_, 1);
    }

    AsioEvent::AsioEvent(const io_event &event) {
        this->io_ = (AsioBlock *)event.obj;
        bytesRead_ = event.res;
    }

    bool Asio::init() {
        int ret = io_setup(64, &context);
        return (ret == 0);
    }

    bool Asio::destroy() const {
        int ret = io_destroy(context);
        return (ret == 0);
    }

    bool Asio::submit(AsioBlock *io) const {
        iocb *pio = static_cast<iocb *>(io);
        auto ret = ::io_submit(context, 1, &pio);
        return (ret == 1);
    }

    bool Asio::cancel(AsioBlock *io) const {
        io_event event{};
        iocb *pio = static_cast<iocb *>(io);
        auto ret = ::io_cancel(context, pio, &event);
        return (ret == 0);
    }

    AsioEvent Asio::getEvent() const {
        io_event event{};
        auto ret = io_getevents(context, 1, 1, &event, nullptr);
        if (ret != 1) { return AsioEvent{}; }
        return AsioEvent{event};
    }
}
