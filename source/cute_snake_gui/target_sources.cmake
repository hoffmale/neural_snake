set(qrc_sources
	${CMAKE_CURRENT_SOURCE_DIR}/qml.qrc
)

set(sources
	${CMAKE_CURRENT_SOURCE_DIR}/board_model.h
	${CMAKE_CURRENT_SOURCE_DIR}/board_model.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qt_controller.h
	${CMAKE_CURRENT_SOURCE_DIR}/qt_controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qt_renderer.h
	${CMAKE_CURRENT_SOURCE_DIR}/qt_renderer.cpp
)

set(qml_dir
	${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB qml_sources ${qml_dir}/*.qml)

list(APPEND ide_sources
	${sources}
	${qml_sources}
)

source_group(
	TREE
		${CMAKE_CURRENT_SOURCE_DIR}
	PREFIX
		"Source Files"
	FILES
		${ide_sources}
)