cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3 -O0")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/home/alexen/devel/cmake")
set(GMOCK_ROOT "/home/alexen/devel/gmock")
set(GMOCK_BUILD "/home/alexen/build/gmock")

find_package(Threads REQUIRED)
find_package(GMock REQUIRED)

include_directories(${GMOCK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

set(LIBNAME authservice)

add_library(${LIBNAME}
    auth_service.cpp
    exception.cpp
)

set(LIBTEST ${LIBNAME}-test)

add_executable(${LIBTEST}
    auth_service_test.cpp
)

target_link_libraries(${LIBTEST}
    ${LIBNAME}
    ${GMOCK_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)