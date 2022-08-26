cmake_minimum_required(VERSION 3.10)
project(Multi-Tetris
	LANGUAGES CXX
)

# use FindSDL2.cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb")

include_directories(	
	src 
	assets
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Tetris.cpp src/Block.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
