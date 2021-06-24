add_executable(myoi_http_test
        http/HttpRequestParserTest.cpp)

target_link_libraries(myoi_http_test myoi_http)
target_link_libraries(myoi_http_test gtest)
target_link_libraries(myoi_http_test fmt)