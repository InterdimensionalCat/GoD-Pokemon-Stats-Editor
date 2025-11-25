cmake_minimum_required (VERSION 3.20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Glob all tool source files
set(TOOL_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
FILE(GLOB_RECURSE TOOL_CPP_FILES ${TOOL_SRC_DIR}/*.cpp)
Message("[INFO]: Data Editor Tool CPP files: ${TOOL_CPP_FILES}")

# Create the executable with all tool files at the top level directory
# as well as the Resources.rc file
add_executable(${PROJECT_NAME} ${TOOL_CPP_FILES} "${RESOURCE_DIR}/Resources.rc"  )

# We want the exectuable to be created at the top level directory, even though we are creating it in the tool's CMakeLists.txt
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add tool include directory
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
