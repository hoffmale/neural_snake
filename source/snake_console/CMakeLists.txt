cmake_minimum_required(VERSION 3.14)

project(snake_console)

add_executable(${PROJECT_NAME})

set(sources
	${CMAKE_CURRENT_SOURCE_DIR}/src/console_input.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/console_renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

set(headers
	${CMAKE_CURRENT_SOURCE_DIR}/src/console_input.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/console_renderer.h
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
	PRIVATE
		snake_brain
)

source_group(
	TREE
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${headers}
		${sources}
)
