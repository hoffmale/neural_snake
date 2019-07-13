cmake_minimum_required(VERSION 3.14)

project(cute_snake_gui)

add_executable(${PROJECT_NAME} WIN32)

set(qrc_sources
	${CMAKE_CURRENT_SOURCE_DIR}/qml/qml.qrc
)

set(sources
	${CMAKE_CURRENT_SOURCE_DIR}/src/board_model.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/board_model.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/qt_controller.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/qt_controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/qt_renderer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/qt_renderer.cpp
)

set(qml_dir
	${CMAKE_CURRENT_SOURCE_DIR}/qml
)

file(GLOB qml_sources ${qml_dir}/*.qml)

source_group(
	TREE
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${sources}
		${qml_sources}
		${qrc_sources}
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		${sources}
		${qrc_sources}
		${qml_sources}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		Qt5::Core
		Qt5::Quick
		neural_snake_lib
		ai_dumb_deterministic
)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
		AUTOMOC ON
		AUTORCC ON
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${PROJECT_NAME}
)

winDeployQtPostBuild(
	TARGET ${PROJECT_NAME}
	QML_DIR ${qml_dir}
)
