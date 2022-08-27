cmake_minimum_required(VERSION 3.10)
project(Multi-Tetris
	LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 11)

# use FindSDL2.cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb")

set(SDL_H ${SDL2_INCLUDE_DIR})
set(SDL_LIB ${SDL2_LIBRARY})

# Create Link for Mac OS X
if(APPLE)
	list(APPEND SDL_H ${SDL2_IMAGE_INCLUDE_DIRS})
	list(APPEND SDL_LIB ${SDL2_IMAGE_LIBRARIES})
endif(APPLE)

# Create Link for Linux
if(UNIX AND NOT APPLE)
	list(APPEND SDL_H ${SDL2_IMAGE_INCLUDE_DIR})
	list(APPEND SDL_LIB ${SDL2_IMAGE_LIBRARY})
endif(UNIX and not APPLE)


include_directories(	
	src 
	assets
	${SDL_H}
)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Tetris.cpp src/Block.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL_LIB})
