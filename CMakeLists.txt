cmake_minimum_required(VERSION 3.12)

project(MqttClientRscService)

#include(CTest)

# Always use find_package to find external dependencies.
# Make find_package a noop for targets that are available as sub projects.
# See speech of Daniel Pfeifer "Effective CMake" C++Now 2017 Slide 34
macro(find_package)
    if(NOT "${ARGV0}" IN_LIST FindAsSubproject)
        _find_package(${ARGV})
    else()
        set("${ARGV0}_FOUND" TRUE)
    endif()
endmacro()

# Add targets that are included as sub projects
# set(FindAsSubproject "MqttClient")

add_subdirectory(libs)
#add_subdirectory(extras)
