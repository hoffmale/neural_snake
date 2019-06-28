cmake_minimum_required(VERSION 3.14)

project(snake_brain)

add_library(${PROJECT_NAME} STATIC)

set(sources
	${CMAKE_CURRENT_SOURCE_DIR}/src/ai_controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ai_feedback.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/back_propagation_trainer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/functions.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/layer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/network.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/network_trainer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/neuron.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/snake_brain.cpp
)

set(headers
	${CMAKE_CURRENT_SOURCE_DIR}/include/ai_controller.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/ai_feedback.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/back_propagation_trainer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/functions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/layer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/math.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/network.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/network_trainer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/neuron.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/ranges.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sample.hpp
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
