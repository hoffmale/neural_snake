cmake_minimum_required(VERSION 3.14)

project(neural_snake_lib)

#include(target_sources.cmake)

add_library(${PROJECT_NAME} STATIC)

set(sources
		${CMAKE_CURRENT_SOURCE_DIR}/src/board.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/simulation.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/snake.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/snake_game.cpp
)

set(headers
		${CMAKE_CURRENT_SOURCE_DIR}/include/board.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/controller.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/direction.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/position.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/renderer.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/simulation.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/snake.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/snake_game.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/tile_content.h
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		${headers}
		${sources}
)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
)

source_group(
	TREE
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${headers}
		${sources}
)
