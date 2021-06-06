cmake_minimum_required(VERSION 3.12)
project(squirhell)

# Set C++ language requirement.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SRC_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Pull latest git submodule update from remote.

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --remote
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

include_directories(${SRC_DIRECTORY})

# Find all cpp files in the src directory of the project.

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false 
    "${SRC_DIRECTORY}/*.h" "${SRC_DIRECTORY}/*.cpp")

if (WIN32)
    # Keep original folder structure for MSVC.

    foreach(_source IN ITEMS ${SRC_FILES})
        get_filename_component(_source_path "${_source}" PATH)
        file(RELATIVE_PATH _source_path_rel "${SRC_DIRECTORY}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()
endif()

# Create executable from all source files.

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Copy resource files over to binary directory.

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources/" DESTINATION ${PROJECT_BINARY_DIR}/resources)

# Add protegon engine to the target executable.
# IMPORTANT NOTE: If using this file as a template for your project, 
# make sure add_subdirectory(<protegon_root_dir>) has been called before.

add_subdirectory("vendor/protegon")
add_protegon_to(${PROJECT_NAME})