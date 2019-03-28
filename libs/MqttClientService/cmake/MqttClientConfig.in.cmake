# Copyright PHOENIX CONTACT Deutschland GmbH
#
# CMake configure file for @PROJECT_NAME@ library

@PACKAGE_INIT@

include(CMakeFindDependencyMacro)

include("${CMAKE_CURRENT_LIST_DIR}/@TargetsExportName@.cmake")
check_required_components("@PROJECT_NAME@")
