
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-narrowing -Wa,-mbig-obj")

#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-narrowing -std=c++11 -Wa,-mbig-obj")

# cmake c++ hello1


cmake_minimum_required(VERSION 3.10)

project(lishi)

set(gs_project_path ${CMAKE_CURRENT_SOURCE_DIR})
set(gs_project_include_path ${gs_project_path}/include)
set(gs_project_3rd_path ${gs_project_path}/3rd)
set(gs_project_hello_path ${gs_project_path}/hello)
set(gs_project_projects_path ${gs_project_path}/projects)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

include(build/cmake/local.config.cmake)
include(build/cmake/utils.cmake)
include(build/cmake/fs.cmake)

add_subdirectory(build/cmake)
