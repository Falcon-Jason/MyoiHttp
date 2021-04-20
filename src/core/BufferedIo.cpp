/**
 * @file network.cpp
 * @author Jason Cheung
 * @date 2021/03/22
 * @brief implementations of network library
 */

#include "core/Network.h"
#include "core/BufferedIo.h"
#include <bits/stdc++.h>
#include <unistd.h>


namespace network {
    BufferedIo::BufferedIo(int fd) {
        // support for operations like `bufio_new(open())`
        // if inner function like `open()` fails, the whole program will exit,
        // which ensures that the poinunics::ter returned is always available.
        if (fd <= 0) {
            Error("`bufio_new()` failed: %s\n",
                  errno == 0 ? "invalid argument `fileDescriptor`" : strerror(errno));
        }

        this->fileDescriptor = fd;
        this->bufferLength = 0;
        this->bufferPointer = this->innerBuffer;
    }

    BufferedIo::~BufferedIo() {
        std::cout << "closed" << std::endl;
        ErrorIf(::close(this->fileDescriptor) != 0, "BufferedIo: close failed: %s.\n", strerror(errno));
    }

    ssize_t BufferedIo::nread(char *userBuffer, size_t length) {
        size_t nleft = length;
        char *buf_ptr = userBuffer;

        while (nleft > 0) {
            ssize_t nread = this->read(buf_ptr, nleft);
            if (nread < 0) {
                return -1;
            } else if (nread == 0) {
                break;  // EOF
            }
            nleft -= nread;
            buf_ptr += nread;
        }
        return (length - nleft);
    }

    ssize_t BufferedIo::nwrite(const char *userBuffer, size_t length) const {
        size_t nleft = length;
        const char *buf_ptr = userBuffer;

        while (nleft > 0) {
            ssize_t nwritten = ::write(this->fileDescriptor, buf_ptr, nleft);
            if (nwritten <= 0) {
                if (nwritten < 0 && errno == EINTR) {
                    nwritten = 0;
                } else {
                    return -1;
                }
            }
            nleft -= nwritten;
            buf_ptr += nwritten;
        }
        return length;
    }

    ssize_t BufferedIo::readline(char *userBuffer, size_t maxLength) {
        char *buf_ptr = userBuffer;
        size_t length;
        for (length = 1; length < maxLength; length++) {
            char ch;
            ssize_t retcode = this->read(&ch, 1);
            if (retcode == 1) {
                *buf_ptr++ = ch;
                if (ch == '\n') {
                    length++;
                    break;
                }
            } else if (retcode == 0) {
                if (length == 1) {
                    return 0;  // no data read
                } else {
                    break;
                }
            } else {
                return -1;
            }
        }
        *buf_ptr = '\0';
        return length - 1;
    }

    [[nodiscard]] int BufferedIo::fd() const {
        return fileDescriptor;
    }

    ssize_t BufferedIo::read(char *buffer, size_t length) {
        // if buffer is empty, read something new from file and store it into the buffer.
        while (this->bufferLength <= 0) {
            this->bufferLength = ::read(this->fileDescriptor, this->innerBuffer, BUFIO_BUFFER_SIZE);
            if (this->bufferLength < 0 && errno != EINTR) {
                return -1;  // ERROR
            } else if (this->bufferLength == 0) {
                return 0;  // EOF
            } else {
                // reset buf_ptr
                this->bufferPointer = this->innerBuffer;
            }
        }

        // copy min(length, file->buf_len) bytes out.
        ssize_t count = length < this->bufferLength ? length : this->bufferLength;
        memcpy(buffer, this->bufferPointer, count);
        this->bufferPointer += count;
        this->bufferLength -= count;
        return count;
    }
};


