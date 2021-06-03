/*
 * I tried to find a beautiful way to convert between enums and strings,
 * but finally I failed.
 * I have to use simple but stupid method to finish it,
 * with TDD to ensure the codes correct;
 */

#include "http/HttpRequest.h"

#include <gtest/gtest.h>

using namespace std;

TEST(TestHttp, TestHttpMethod) {
    http::HttpMethod method;
    method = http::HttpMethod::GET;
    ASSERT_STREQ(http::ToString(method), "GET");
    method = http::HttpMethod::POST;
    ASSERT_STREQ(http::ToString(method), "POST");
    method = http::HttpMethod::HEAD;
    ASSERT_STREQ(http::ToString(method), "HEAD");

    ASSERT_TRUE(http::FromString("GET", method));
    ASSERT_EQ(method, http::HttpMethod::GET);
    ASSERT_TRUE(http::FromString("POST", method));
    ASSERT_EQ(method, http::HttpMethod::POST);
    ASSERT_TRUE(http::FromString("HEAD", method));
    ASSERT_EQ(method, http::HttpMethod::HEAD);

    ASSERT_FALSE(http::FromString("GOT", method));
    ASSERT_FALSE(http::FromString("GETTING", method));
    ASSERT_FALSE(http::FromString("get", method));
}

TEST(TestHttp, TestHttpVersion) {
    http::HttpVersion version;

    version = http::HttpVersion::HTTP_0_9;
    ASSERT_STREQ(http::ToString(version), "HTTP/0.9");
    version = http::HttpVersion::HTTP_1_0;
    ASSERT_STREQ(http::ToString(version), "HTTP/1.0");
    version = http::HttpVersion::HTTP_1_1;
    ASSERT_STREQ(http::ToString(version), "HTTP/1.1");

    ASSERT_TRUE(http::FromString("HTTP/0.9", version));
    ASSERT_EQ(version, http::HttpVersion::HTTP_0_9);
    ASSERT_TRUE(http::FromString("HTTP/1.0", version));
    ASSERT_EQ(version, http::HttpVersion::HTTP_1_0);
    ASSERT_TRUE(http::FromString("HTTP/1.1", version));
    ASSERT_EQ(version, http::HttpVersion::HTTP_1_1);
}
