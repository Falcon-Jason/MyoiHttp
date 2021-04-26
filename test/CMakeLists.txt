add_executable(CoreTest CoreTest.cpp)
target_link_libraries(CoreTest libMyoiCore)
target_link_libraries(CoreTest gtest)
target_link_libraries(CoreTest fmt)