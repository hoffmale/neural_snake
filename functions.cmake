function(setSingleOrMultipleConfigurationTypes)
	set(CMAKE_CONFIGURATION_TYPES 
		Release
		Debug
		RelWithDebInfo
		PARENT_SCOPE
	)
endfunction()

function(enableAutoMocSupport)
	get_target_property(Qt5Version Qt5::Core VERSION)
	
	string(REPLACE "." ";" Qt5VersionList ${Qt5Version})
	
	list(GET Qt5VersionList 0 Qt5Core_VERSION_MAJOR)
	list(GET Qt5VersionList 1 Qt5Core_VERSION_MINOR)
	list(GET Qt5VersionList 2 Qt5Core_VERSION_PATCH)
	
	set(Qt5Core_VERSION_MAJOR ${Qt5Core_VERSION_MAJOR} PARENT_SCOPE)
	set(Qt5Core_VERSION_MINOR ${Qt5Core_VERSION_MINOR} PARENT_SCOPE)
	set(Qt5Core_VERSION_PATCH ${Qt5Core_VERSION_PATCH} PARENT_SCOPE)
endfunction()

function(copyFilesPostBuild)
	set(singleValArgs TARGET DESTINATION)
	set(multiValArgs FILES_TO_COPY)
	cmake_parse_arguments(ARGS "" "${singleValArgs}" "${multiValArgs}" ${ARGN})
	
	if(NOT(ARGS_TARGET AND ARGS_FILES_TO_COPY))
		message(FATAL_ERROR "Missing arguments in copyFilesPostBuild")
	endif()
	
	if(NOT(ARGS_DESTINATION))
		get_target_property(targetOutputDirectory ${ARGS_TARGET} RUNTIME_OUTPUT_DIRECTORY)
	else()
		set(targetOutputDirectory ${ARGS_DESTINATION})
	endif()
	
	foreach(path IN LISTS ARGS_FILES_TO_COPY)
		get_filename_component(filename ${path} NAME)
		add_custom_command(
			TARGET ${ARGS_TARGET}
			COMMAND ${CMAKE_COMMAND} -E copy_if_different ${path} ${targetOutputDirectory}/${filename}
		)
	endforeach()
endfunction()

function(copyDllsPostBuild)
	set(singleValArgs TARGET DESTINATION)
	set(multiValArgs LINKED_TARGETS)
	cmake_parse_arguments(ARGS "" "${singleValArgs}" "${multiValArgs}" ${ARGN})
	
	if(NOT(ARGS_TARGET AND ARGS_LINKED_TARGETS))
		message(FATAL_ERROR "Missing arguments in copyDllsPostBuild")
	endif()
	
	foreach(link_target IN LISTS ARGS_LINKED_TARGETS)
		get_target_property(path ${link_target} IMPORTED_LOCATION)
		list(APPEND dlls_to_copy ${path})
	endforeach()
	
	copyFilesPostBuild(
		TARGET
			${ARGS_TARGET}
		FILES_TO_COPY
			${dlls_to_copy}
		DESTINATION
			${ARGS_DESTINATION}
	)
endfunction()

function(winDeployQtPostBuild)
	set(singleValArgs TARGET QML_DIR)
	cmake_parse_arguments(ARGS "" "${singleValArgs}" "" ${ARGN})
	
	if(NOT(ARGS_TARGET))
		message(FATAL_ERROR "Missing arguments in winDeployQtPostBuild")
	endif()
	
	find_program(
		windeployqtexe
		NAMES
			windeployqt
		HINTS
			${QT5_PATH}
		PATH_SUFFIXES
			bin
	)
	
	if(windeployqtexe)
		set(current_config $<$<CONFIG:Debug>:debug>$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:release>)
		
		if(ARGS_QML_DIR)
			set(qml_dir_flag --qmldir ${ARGS_QML_DIR})
		endif()
		
		add_custom_command(
			TARGET ${ARGS_TARGET}
			POST_BUILD
			COMMAND
				set PATH="" &&
				${windeployqtexe} --${current_config} ${qml_dir_flag} --no-translations --verbose 0 $<TARGET_FILE:${ARGS_TARGET}>
		)
	else()
		message(WARNING "Could not find windeployqt.exe")
	endif()
endfunction()