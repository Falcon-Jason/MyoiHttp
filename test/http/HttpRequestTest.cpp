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
    myoi::HttpMethod method;
    method = myoi::HttpMethod::GET;
    ASSERT_STREQ(myoi::ToString(method), "GET");
    method = myoi::HttpMethod::POST;
    ASSERT_STREQ(myoi::ToString(method), "POST");
    method = myoi::HttpMethod::HEAD;
    ASSERT_STREQ(myoi::ToString(method), "HEAD");

    ASSERT_TRUE(myoi::FromString("GET", method));
    ASSERT_EQ(method, myoi::HttpMethod::GET);
    ASSERT_TRUE(myoi::FromString("POST", method));
    ASSERT_EQ(method, myoi::HttpMethod::POST);
    ASSERT_TRUE(myoi::FromString("HEAD", method));
    ASSERT_EQ(method, myoi::HttpMethod::HEAD);

    ASSERT_FALSE(myoi::FromString("GOT", method));
    ASSERT_FALSE(myoi::FromString("GETTING", method));
    ASSERT_FALSE(myoi::FromString("get", method));
}

TEST(TestHttp, TestHttpVersion) {
    myoi::HttpVersion version;

    version = myoi::HttpVersion::HTTP_0_9;
    ASSERT_STREQ(myoi::ToString(version), "HTTP/0.9");
    version = myoi::HttpVersion::HTTP_1_0;
    ASSERT_STREQ(myoi::ToString(version), "HTTP/1.0");
    version = myoi::HttpVersion::HTTP_1_1;
    ASSERT_STREQ(myoi::ToString(version), "HTTP/1.1");

    ASSERT_TRUE(myoi::FromString("HTTP/0.9", version));
    ASSERT_EQ(version, myoi::HttpVersion::HTTP_0_9);
    ASSERT_TRUE(myoi::FromString("HTTP/1.0", version));
    ASSERT_EQ(version, myoi::HttpVersion::HTTP_1_0);
    ASSERT_TRUE(myoi::FromString("HTTP/1.1", version));
    ASSERT_EQ(version, myoi::HttpVersion::HTTP_1_1);
}
