/**
 * @file test_bufio/main.c
 * @author Jason Cheung
 * @date 2021/03/22
 * @brief unit tests for network_core library
 */
#include "core/BufferedIo.h"
#include "core/Ipv4Addr.h"

#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include <unistd.h>
#include <arpa/inet.h>
};

using namespace network;

BufferedIo test_createfile(const char *text, size_t length) {
    int pipe_fd[2];
    pipe(pipe_fd);

    auto file_in = BufferedIo(pipe_fd[1]);
    auto file_out = BufferedIo(pipe_fd[0]);
    file_in.nwrite(text, length);

    return file_out;
}

void test_bufio_nread(const char *text, char *buffer, size_t length) {
    auto file = test_createfile(text, length);
    file.nread(buffer, length);
    ASSERT_TRUE(memcmp(text, buffer, length) == 0);
}

void test_bufio_readline(const char *text, char *buffer, size_t buffer_length) {
    auto file = test_createfile(text, strlen(text));
    file.readline(buffer, buffer_length);
    ASSERT_TRUE(strncmp(text, buffer, buffer_length - 1) == 0);
}


TEST(BufferedIo, BufferedIo) {
    char buffer_in[4096] = "hello world";
    char buffer_out[4096];
    test_bufio_nread(buffer_in, buffer_out, strlen(buffer_in));
    test_bufio_nread(buffer_in, buffer_out, sizeof(buffer_out));
    test_bufio_readline(buffer_in, buffer_out, sizeof(buffer_out));
    test_bufio_readline(buffer_in, buffer_out, 5);

}

TEST(Ipv4Address, Ipv4Address_Addr) {
    Ipv4Address address{"", 1234};
    ASSERT_FALSE(address.available());
    address.setIp("123.456.7.8");
    ASSERT_FALSE(address.available());
    address.setIp("255.255");
    ASSERT_FALSE(address.available());
    address.setIp("127.0.0.1");
    ASSERT_TRUE(address.available());
    ASSERT_STREQ(address.ip(), "127.0.0.1");
}

TEST(Ipv4Address, Ipv4Address_Port) {
    Ipv4Address address{"127.0.0.1", 1234};
    ASSERT_EQ(address.port(), 1234);
    address.setPort(2048);
    ASSERT_EQ(address.port(), 2048);
}



TEST(Ipv4Address, Ipv4Address_TryListen) {
    auto address = Ipv4Address{"127.0.0.1", 2048};
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    int retCode;
    retCode = ::bind(fd, address.socketAddress(), sizeof(sockaddr_in));
    ASSERT_EQ(retCode, 0);
    retCode = ::listen(fd, 1024);
    ASSERT_EQ(retCode, 0);
    close(fd);
}

inline void Ipv4Address_TestOperateUnixAddr(unsigned int ipInInteger, const char *ipInString, short port) {
    ::sockaddr_in unixAddr{};
    memset(&unixAddr, 0, sizeof(unixAddr));
    unixAddr.sin_addr.s_addr = ::htonl(ipInInteger);
    unixAddr.sin_port = ::htons(port);
    Ipv4Address addr{unixAddr};
    ASSERT_STREQ(addr.ip(), ipInString);
    ASSERT_EQ(addr.port(), port);
}

TEST(Ipv4Address, Ipv4Address_OperateUnixAddr) {
    Ipv4Address_TestOperateUnixAddr(0, "0.0.0.0", 80);
    Ipv4Address_TestOperateUnixAddr(0xC0A80101, "192.168.1.1", 1024);
    Ipv4Address_TestOperateUnixAddr(0x7F000001, "127.0.0.1", 0);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}