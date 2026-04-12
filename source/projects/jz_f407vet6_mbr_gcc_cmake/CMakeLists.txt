cmake_minimum_required(VERSION 3.16)
project(jz_f407vet6_mbr_gcc_cmake)
set(PROJECT_NAME jz_f407vet6_mbr_gcc_cmake)
enable_language(C ASM)

set(CURRENT_CMAKELISTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "CURRENT_CMAKELISTS_DIR=${CURRENT_CMAKELISTS_DIR}")

set(PROJECT_LOC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${PROJECT_LOC})

set(BUILD_DIR ${PROJECT_LOC}/build)

set(TARGET ${PROJECT_NAME})
set(EXECUTABLE ${TARGET})

get_filename_component(WORKSPACE_LOC "${PROJECT_LOC}/../.." ABSOLUTE)
message(STATUS "WORKSPACE_LOC=${WORKSPACE_LOC}")
include_directories(${WORKSPACE_LOC})
message(STATUS "PROJECT_LOC=${PROJECT_LOC}")

include(${PROJECT_LOC}/config.cmake)
include(${WORKSPACE_LOC}/cmake_scripts/code_base.cmake)
include(${WORKSPACE_LOC}/cmake_scripts/rules.cmake)
