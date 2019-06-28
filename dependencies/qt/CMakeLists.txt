cmake_minimum_required(VERSION 3.14)

list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})

set(QT_VERSION 5.12.2)

find_package(
	Qt5 ${QT_VERSION} EXACT
	REQUIRED COMPONENTS
		Core
		Quick
)

if(Qt5_FOUND)
	set_target_properties(
		Qt5::Core
		Qt5::Quick
		Qt5::moc
		Qt5::rcc
		PROPERTIES
			IMPORTED_GLOBAL TRUE
			VERSION "${Qt5Core_VERSION_MAJOR}.${Qt5Core_VERSION_MINOR}.${Qt5Core_VERSION_PATH}"
	)
endif()