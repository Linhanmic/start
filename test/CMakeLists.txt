set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)


add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test start)
add_executable(pthread_test pthread_test.cpp)
target_link_libraries(pthread_test pthread start)