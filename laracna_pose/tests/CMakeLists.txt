cmake_minimum_required(VERSION 3.16)

# Nome do projeto de testes
project(test_my_module)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include")
set(UNITY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../external/Unity/src")


include_directories(include)

set(SOURCES
    test_vector3.cpp
)


include_directories(${INCLUDE_DIR} ${UNITY_DIR})

add_library(unity STATIC "${UNITY_DIR}/unity.c")

add_executable(test_runner ${SOURCES})

target_link_libraries(test_runner PRIVATE pthread unity)