cmake_minimum_required(VERSION 3.12)

project(squirhell)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SQUIRHELL_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories(SQUIRHELL_SRC_DIR)

file(GLOB_RECURSE SQUIRHELL_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false 
     "${SQUIRHELL_SRC_DIR}/*.h" "${SQUIRHELL_SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SQUIRHELL_FILES})

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources/" DESTINATION "${PROJECT_BINARY_DIR}/resources")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../protegon" binary_dir)
add_protegon_to(${PROJECT_NAME})

if (WIN32)
    foreach(_source IN ITEMS ${SQUIRHELL_FILES})
		get_filename_component(_source_path "${_source}" PATH)
		file(RELATIVE_PATH _source_path_rel "${SQUIRHELL_SRC_DIR}" "${_source_path}")
		string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
		source_group("${_group_path}" FILES "${_source}")
	endforeach()
endif()