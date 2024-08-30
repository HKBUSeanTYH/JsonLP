cmake_minimum_required(VERSION 3.0)
project(JsonLP VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include(CTest)
# enable_testing()

# source files
set(SOURCES src/main.cpp)

# executable
add_executable(${PROJECT_NAME} ${SOURCES})