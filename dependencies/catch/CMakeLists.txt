cmake_minimum_required(VERSION 3.14)

list(APPEND CMAKE_PREFIX_PATH ${CATCH_PATH})

find_package(Catch2 REQUIRED)

if(Catch2_FOUND)
	set_target_properties(
		Catch2::Catch2
		PROPERTIES
			IMPORTED_GLOBAL TRUE
	)
endif()