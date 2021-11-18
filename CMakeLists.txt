cmake_minimum_required(VERSION 3.0.0)
project(GameOfLifeSDL VERSION 0.1.0)

# Find the SDL2 library
find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
include_directories(${SDL2_INCLUDE_DIR})

include(CTest)
include_directories(Src)
enable_testing()

set (CMAKE_CXX_STANDARD 20)
add_executable(GameOfLifeSDL 
main.cpp
Src/Graphics.cpp
Src/GameOfLife.cpp
Src/GameOfLife.h
Src/Graphics.h
${SDL2_LIBRARY})

target_link_libraries(GameOfLifeSDL ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
