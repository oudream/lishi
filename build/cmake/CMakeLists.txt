
cmake_minimum_required(VERSION 3.10)

project(lishi)

if (NOT gc_project_path)
    set(gs_project_path ${CMAKE_CURRENT_SOURCE_DIR}/../..)
endif ()

include(local.config.cmake)
include(utils.cmake)
include(fs.cmake)

#
add_subdirectory(ccxx)
#
add_subdirectory(hello)
#
add_subdirectory(projects)
