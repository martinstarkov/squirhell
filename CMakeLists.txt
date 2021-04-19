cmake_minimum_required(VERSION 3.12)
project(squirhell)

# Set C++ language requirement.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/vendor/protegon/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# Add include directories to project.

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Keeps the filter structure

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")
file(
    GLOB_RECURSE _source_list 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_src_root_path}/*.cpp"
    "${_src_root_path}/*.h"
)

foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
    source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()

# Find all cpp files in the src directory of the project.

file(GLOB_RECURSE FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

# Create executable from all source files.

add_executable(
    ${PROJECT_NAME}
    ${FILES}
)

# Copy resource files over to binary directory.

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources/" DESTINATION ${PROJECT_BINARY_DIR}/resources)

# Add protegon engine to the target executable.
# IMPORTANT NOTE: If using this file as a template for your project, 
# make sure add_subdirectory(<protegon_root_dir>) has been called before.

add_subdirectory("vendor/protegon")
add_protegon_to(${PROJECT_NAME})