add_executable(CoreTest CoreTest.cpp)
target_link_libraries(CoreTest MyoiHttp_Core)
target_link_libraries(CoreTest gtest)
target_link_libraries(CoreTest fmt)

#add_executable(HttpTest HttpTest.cpp)
#target_link_libraries(HttpTest MyoiHttp_Http)
#target_link_libraries(HttpTest MyoiHttp_Core)
#target_link_libraries(HttpTest gtest)