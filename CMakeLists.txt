cmake_minimum_required(VERSION 3.0.0)
project(ChessGame VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
file(GLOB SOURCES "src/lib/*.cpp")

add_executable(ChessGame src/main.cpp ${SOURCES})
target_link_libraries(ChessGame SDL2main SDL2 SDL2_image)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
