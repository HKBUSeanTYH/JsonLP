cmake_minimum_required(VERSION 3.0)
project(JsonLP VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include(CTest)
# enable_testing()

# source files
set(SOURCES src/LexerStackVectorOperations.cpp src/LexerStreamOperations.cpp src/Parser.cpp src/JsonNode.cpp src/LexToken.cpp src/NumericString.cpp src/main.cpp)
set(INCLUDES include)
file(COPY resources DESTINATION .)

# executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})