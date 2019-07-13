cmake_minimum_required(VERSION 3.14)

project(ai_dumb_deterministic)

add_library(${PROJECT_NAME} STATIC)

set(headers
	${CMAKE_CURRENT_SOURCE_DIR}/include/dumb_controller.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dumb_nn_ai.hpp
)

set(sources
	${CMAKE_CURRENT_SOURCE_DIR}/src/dumb_controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/dumb_nn_ai.cpp
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

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		snake_brain
		neural_network_lib
)

source_group(
	TREE
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${headers}
		${sources}
)
