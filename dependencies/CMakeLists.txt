cmake_minimum_required(VERSION 3.14)

project(dependencies)

set(folder ${PROJECT_NAME})

add_subdirectory(qt)
add_subdirectory(catch)

# fix qt version for cmake
get_target_property(Qt5Version Qt5::Core VERSION)
string(REPLACE "." ";" Qt5VersionList ${Qt5Version})
list(GET Qt5VersionList 0 Qt5Core_VERSION_MAJOR)
list(GET Qt5VersionList 1 Qt5Core_VERSION_MINOR)
list(GET Qt5VersionList 2 Qt5Core_VERSION_PATCH)
set(Qt5Core_VERSION_MAJOR ${Qt5Core_VERSION_MAJOR} PARENT_SCOPE)
set(Qt5Core_VERSION_MINOR ${Qt5Core_VERSION_PATCH} PARENT_SCOPE)
set(Qt5Core_VERSION_PATCH ${Qt5Core_VERSION_MINOR} PARENT_SCOPE)