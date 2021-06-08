//
// Created by jason on 3/6/21.
//

#include "core/Asio.h"

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

    AsioEvent::~AsioEvent() {
        clear();
    }

    void AsioEvent::clear() {
        if (buffer_ != nullptr) {
            delete[] buffer_;
            buffer_ = nullptr;
        }
    }

    size_t AsioEvent::bufferSize() const {
        if (type_ != SocketType::CONNECTION) { return 0; }
        return u.c.nbytes;
    }

    AsioEvent *AsioEvent::MakeRead(TcpSocket &connection, size_t size) {
        auto *event = new AsioEvent{};
        event->clear();
        event->buffer_ = new char[size];
        event->type_ = SocketType::CONNECTION;
        io_prep_pread(static_cast<iocb *>(event), connection.socket_, event->buffer_, size, 0);
        return event;
    }

    AsioEvent *AsioEvent::MakePoll(TcpSocket &listener) {
        auto *event = new AsioEvent{};
        event->clear();
        event->type_ = SocketType::LISTENER;
        io_prep_poll(static_cast<iocb *>(event), listener.socket_, 1);
        return event;
    }

    bool Asio::init() {
        int ret = io_setup(64, &context);
        return (ret == 0);
    }

    bool Asio::submit(AsioEvent *io) const {
        iocb *pio = static_cast<iocb *>(io);
        auto ret = ::io_submit(context, 1, &pio);
        return (ret == 1);
    }

    AsioEvent * Asio::getEvent() const {
        io_event event{};
        auto ret = io_getevents(context, 1, 1, &event, nullptr);
        if (ret != 1) { return nullptr; }
        AsioEvent *result = (AsioEvent *)(event.obj);
        result->byteRead_ = event.res;
        return result;
    }
}
