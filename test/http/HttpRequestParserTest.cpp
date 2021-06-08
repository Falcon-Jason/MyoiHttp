//
// Created by jason on 30/5/21.
//

#include <gtest/gtest.h>
#include <fmt/format.h>
#include "http/HttpRequestParser.h"

#define LONG_URI "http://www.baidu.com/index.html?id=123456"

TEST(TestHttpRequestParser, ParseRequestLineOnly) {
    myoi::HttpRequestParser parser{};
    ASSERT_TRUE(parser.open());
    ASSERT_FALSE(parser.success());
    ASSERT_FALSE(parser.failure());

    parser.parse("HEAD /index.html HTTP/1.0\r\n\r\n");
    ASSERT_TRUE(parser.success());
    ASSERT_EQ(parser.request().method(), myoi::HttpMethod::HEAD);
    ASSERT_STREQ(parser.request().uri(), "/index.html");
    ASSERT_EQ(parser.request().version(), myoi::HttpVersion::HTTP_1_0);

    parser.clear();
    ASSERT_TRUE(parser.open());
    parser.parse("POST " LONG_URI " HTTP/1.1\r\n\r\n");
    ASSERT_TRUE(parser.success());
    ASSERT_EQ(parser.request().method(), myoi::HttpMethod::POST);
    ASSERT_STREQ(parser.request().uri(), LONG_URI);
    ASSERT_EQ(parser.request().version(), myoi::HttpVersion::HTTP_1_1);

    parser.clear();
    parser.parse("GET /\r\n\r\n");
    ASSERT_TRUE(parser.success());
    ASSERT_EQ(parser.request().method(), myoi::HttpMethod::GET);
    ASSERT_STREQ(parser.request().uri(), "/");
    ASSERT_EQ(parser.request().version(), myoi::HttpVersion::HTTP_0_9);

    parser.clear();
    parser.parse("\r\n");
    ASSERT_TRUE(parser.failure());

}

TEST(TestHttpRequestParser, ParseChromeRequest) {
    const std::map<std::string, std::string> headers{
        {"Host", "localhost:4321"},
        {"Connection", "keep-alive"},
        {"Cache-Control", "max-age=0"},
        {"sec-ch-ua", R"("Chromium";v="91", " Not;A Brand";v="99")"},
        {"sec-ch-ua-mobile", "?0"},
        {"Upgrade-Insecure-Requests", "1"},
        {"User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.77 Safari/537.36"},
        {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9"},
        {"Sec-Fetch-Site", "none"},
        {"Sec-Fetch-Mode", "navigate"},
        {"Sec-Fetch-User", "?1"},
        {"Sec-Fetch-Dest", "document"},
        {"Accept-Encoding", "gzip, deflate, br"},
        {"Accept-Language", "zh-CN,zh;q=0.9"}};

    myoi::HttpRequestParser parser{};
    parser.parse("GET " LONG_URI " HTTP/1.0\r\n");
    ASSERT_TRUE(parser.open());
    for (auto& header : headers) {
        auto line = fmt::format("{0}: {1}\r\n", header.first, header.second);
        parser.parse(line.c_str());
        ASSERT_TRUE(parser.open());
    }

    parser.parse("\r\n");
    ASSERT_TRUE(parser.success());

    const auto& reqHeaders = parser.request().headers();
    ASSERT_EQ(headers.size(), reqHeaders.size());
    for (auto i = headers.begin(), j = reqHeaders.begin();
         i != headers.end() && j != headers.end(); ++i, ++j) {
        ASSERT_EQ(i->first, j->first);
        ASSERT_EQ(i->second, j->second);
    }
}
