cmake_minimum_required(VERSION 3.13)

project(PxceTcs.Mqtt.Client)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

################# create target #######################################################

set (WILDCARD_SOURCE *.cpp)
set (WILDCARD_HEADER *.h *.hpp *.hxx)

file(GLOB_RECURSE Headers src/${WILDCARD_HEADER} )
file(GLOB_RECURSE Sources src/${WILDCARD_SOURCE} )
add_library(PxceTcs.Mqtt.Client SHARED ${Headers} ${Sources})

#######################################################################################

################# project include-paths ###############################################

target_include_directories(PxceTcs.Mqtt.Client
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/intermediate/code>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

#######################################################################################

################# include arp cmake module path #######################################

list(INSERT CMAKE_MODULE_PATH 0 "${ARP_TOOLCHAIN_CMAKE_MODULE_PATH}")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#######################################################################################

################# set link options ####################################################
# WARNING: Without --no-undefined the linker will not check, whether all necessary    #
#          libraries are linked. When a library which is necessary is not linked,     #
#          the firmware will crash and there will be NO indication why it crashed.    #
#######################################################################################

target_link_options(PxceTcs.Mqtt.Client PRIVATE LINKER:--no-undefined)

#######################################################################################

################# add link targets ####################################################

find_package(ArpDevice REQUIRED)
find_package(ArpProgramming REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(PahoMqttCS REQUIRED)
find_package(PahoMqttAS REQUIRED)

target_link_libraries(PxceTcs.Mqtt.Client PRIVATE ArpDevice ArpProgramming
                        PahoMqttCpp::paho-mqttpp3
                        PahoMqttCS::PahoMqttCS PahoMqttAS::PahoMqttAS)

#######################################################################################

################# install ############################################################

string(REGEX REPLACE "^.*\\(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+).*$" "\\1" _ARP_SHORT_DEVICE_VERSION ${ARP_DEVICE_VERSION})
install(TARGETS PxceTcs.Mqtt.Client
    LIBRARY DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/lib
    ARCHIVE DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/lib
    RUNTIME DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/bin)
unset(_ARP_SHORT_DEVICE_VERSION)

#######################################################################################
