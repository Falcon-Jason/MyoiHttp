/**
 * @file network.h
 * @author Jason Cheung
 * @date 2021/03/22
 * @brief API definations of network library
 */

#ifndef NETWORK_BUFFEREDIO_H
#define NETWORK_BUFFEREDIO_H

#include <sys/types.h>

namespace network {
    /**
     * buffered I/O Stream for network programming.
     */
    class BufferedIo {
    private:
        /**
        * @brief read at most `length` bytes from file to buffer;
        * it is the replacement of unix `read()` function,
        * which checks the inner buffer for data;
        * @param buffer where the read bytes to be saved;
        * @param length the length of `buffer`
        * @return the actual count of bytes read from file;
        */
        ssize_t read(char *buffer, size_t length);

    public:
        /**
         * create a buffered stream and bind a UNIX file-descriptor to it
         * @param fd the file-descriptor to be bound
         */
        explicit BufferedIo(int fd);

        /**
         * destruct the buffered stream and close the file
         */
        ~BufferedIo();

        /**
         * read `length` bytes to `userBuffer`;
         * this function may cause the thread blocked,
         * if the `file` is a network network or standard input
         * until there are enough bytes to be read;
         * @param userBuffer where the data saved;
         * @param length the length of userBuffer;
         * @return the actual count of bytes read from file;
         * if the `file` is end(EOF), the return value may be less
         * than `length`;
         * if some error occurred when reading, the return value would
         * be less than 0;
         */
        ssize_t nread(char *userBuffer, size_t length);

        /**
         * read a line ends with '\n'
         * or `maxLength` bytes to userBuffer;
         * @param userBuffer where the data saved;
         * @param maxLength the maximum length to be read;
         * @return the actual count of bytes read from file;
         */
        ssize_t readline(char *userBuffer, size_t maxLength);

        /**
         * write length bytes from userBuffer
         * @param userBuffer the source of bytes
         * @param length the length of `userBuffer`
         * @return the actual count of bytes written to `file`;
         * if some error occurred when reading, the return value would
         * be less than 0;
         */
        ssize_t nwrite(const char *userBuffer, size_t length) const;

        /**
         * get the UNIX file descriptor of current stream
         * @return the file descriptor
         */
        int fd() const;

    private:
        static constexpr ssize_t BUFIO_BUFFER_SIZE = 4096;

        int fileDescriptor{};                     // file descriptor
        ssize_t bufferLength{};                   // the unread bytes in buffer
        char *bufferPointer{};                    // the pointer to unread bytes
        char innerBuffer[BUFIO_BUFFER_SIZE]{};    // the buffer
    };
};

#endif  // NETWORK_BUFFEREDIO_H
