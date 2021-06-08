add_executable(myoi_http_test
        http/HttpRequestParserTest.cpp
        http/HttpRequestTest.cpp
        http/main.cpp)

target_link_libraries(myoi_http_test myoi_http)
target_link_libraries(myoi_http_test gtest)
target_link_libraries(myoi_http_test fmt)

#add_executable(test test.cpp)
#target_link_libraries(test myoi_core aio)