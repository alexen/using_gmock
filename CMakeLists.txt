cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/home/alexen/devel/cmake")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

set(ENV{GMOCK_ROOT} "/home/alexen/downloads/gmock-1.7.0")
set(ENV{GMOCK_BUILD} "/home/alexen/downloads/gmock-1.7.0")
set(ENV{GTEST_ROOT} "/home/alexen/downloads/gtest-1.7.0")

find_package(Threads REQUIRED)
find_package(GMock REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GMOCK_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

set(NAME authservice)

add_library(${NAME} SHARED
    auth_service.cpp
)

set(UTNAME ${NAME}-test)

add_executable(${UTNAME}
    auth_service_test.cpp
)

target_link_libraries(${UTNAME}
    ${NAME}
    ${GMOCK_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)