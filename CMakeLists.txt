cmake_minimum_required(VERSION 3.18)

project(vlogger)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vlogger.cpp)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/inc/vlogger.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
