add_executable(test_core CoreTest.cpp)
target_link_libraries(test_core MyoiHttp_Core)
target_link_libraries(test_core gtest)
