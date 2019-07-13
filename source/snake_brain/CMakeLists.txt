cmake_minimum_required(VERSION 3.14)

project(snake_brain)

add_library(${PROJECT_NAME} STATIC)

set(sources
	${CMAKE_CURRENT_SOURCE_DIR}/src/ai_controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ai_feedback.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/snake_brain.cpp
)

set(headers
	${CMAKE_CURRENT_SOURCE_DIR}/include/ai_controller.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/ai_feedback.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/snake_brain.h
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

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		neural_network_lib
		neural_snake_lib
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
