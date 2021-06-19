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
    myoi::HttpMethod method{myoi::HttpMethod::GET};

    method = myoi::HttpMethod::HEAD;
    ASSERT_STREQ(method.toString(), "HEAD");
    method = myoi::HttpMethod::GET;
    ASSERT_STREQ(method.toString(), "GET");
    method = myoi::HttpMethod::POST;
    ASSERT_STREQ(method.toString(), "POST");

    ASSERT_TRUE(myoi::HttpMethod::parse(method, "HEAD"));
    ASSERT_EQ(method, myoi::HttpMethod::HEAD);
    ASSERT_TRUE(myoi::HttpMethod::parse(method, "GET"));
    ASSERT_EQ(method, myoi::HttpMethod::GET);
    ASSERT_TRUE(myoi::HttpMethod::parse(method, "POST"));
    ASSERT_EQ(method, myoi::HttpMethod::POST);


    ASSERT_FALSE(myoi::HttpMethod::parse(method, "GOT"));
    ASSERT_FALSE(myoi::HttpMethod::parse(method, "GETTING"));
    ASSERT_FALSE(myoi::HttpMethod::parse(method, "get"));
}

TEST(TestHttp, TestHttpVersion) {
    myoi::HttpVersion version{myoi::HttpVersion::HTTP_1_0};

    version = myoi::HttpVersion::HTTP_0_9;
    ASSERT_STREQ(version.toString(), "HTTP/0.9");
    version = myoi::HttpVersion::HTTP_1_0;
    ASSERT_STREQ(version.toString(), "HTTP/1.0");
    version = myoi::HttpVersion::HTTP_1_1;
    ASSERT_STREQ(version.toString(), "HTTP/1.1");

    ASSERT_TRUE(myoi::HttpVersion::parse(version, "HTTP/0.9"));
    ASSERT_EQ(version, myoi::HttpVersion::HTTP_0_9);
    ASSERT_TRUE(myoi::HttpVersion::parse(version, "HTTP/1.0"));
    ASSERT_EQ(version, myoi::HttpVersion::HTTP_1_0);
    ASSERT_TRUE(myoi::HttpVersion::parse(version, "HTTP/1.1"));
    ASSERT_EQ(version, myoi::HttpVersion::HTTP_1_1);


    ASSERT_FALSE(myoi::HttpVersion::parse(version, "HTTP/1.5"));
    ASSERT_FALSE(myoi::HttpVersion::parse(version, "HTTP/2.0"));
    ASSERT_FALSE(myoi::HttpVersion::parse(version, "HTTP/1.10"));
    ASSERT_FALSE(myoi::HttpVersion::parse(version, "HTTP"));
}
