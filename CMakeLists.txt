cmake_minimum_required(VERSION 3.14)

project(neural_snake)

include(config.cmake)
include(functions.cmake)

setSingleOrMultipleConfigurationTypes()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/tests)

set_property(
	GLOBAL PROPERTY
		USE_FOLDERS ON
)

enable_testing()

add_subdirectory(dependencies)
enableAutoMocSupport()
add_subdirectory(source)