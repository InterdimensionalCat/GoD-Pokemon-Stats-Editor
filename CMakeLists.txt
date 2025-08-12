cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (MSVC)
    set_target_properties(${BUILD_TARGET} PROPERTIES LINK_FLAGS "/PROFILE")
endif()

# Remove wchar nonsense
add_compile_options(/Zc:wchar_t-)

# Force UTF-8 interpretation
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Set project name
set(PROJECT_NAME "IC-GoD-DataEditorTool")
project(${PROJECT_NAME})

# Set Project resource and dependency directory
set(RESOURCE_DIR "${PROJECT_SOURCE_DIR}/Resources")
set(DEPENDENCY_DIR "${PROJECT_SOURCE_DIR}/Dependencies")

# Add resource files to the build
FILE(COPY ${RESOURCE_DIR} DESTINATION "${CMAKE_BINARY_DIR}")

# Add source files to the build and source include directories
add_subdirectory("${PROJECT_SOURCE_DIR}/DataEditorTool")

# Set the C++ standard to C++23 if supported
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
endif()

# Enable debug mode
# TODO: make sure I never use the debug_mode definition from before
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(MESSAGE_QUIET ON)
    message(STATUS "[INFO]: Building on debug mode; IC_DEBUG defined")
    set(MESSAGE_QUIET OFF)
    target_compile_definitions(${PROJECT_NAME} PUBLIC IC_DEBUG)
endif()

# Dependency configurations:

# Copy all dependency dll files to build destination, and glob the correct lib files for the configuration.
if(CMAKE_BUILD_TYPE MATCHES Debug)
    FILE(GLOB EXT_LIBS ${DEPENDENCY_DIR}/lib/Debug/*.lib)

    # Currently no dynamically linked libraries used, if they ever are used this will be needed.
    # FILE(GLOB EXT_DLL  ${DEPENDENCY_DIR}/bin/Debug/*.dll)
    # FILE(COPY ${EXT_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
else()
    FILE(GLOB EXT_LIBS ${DEPENDENCY_DIR}/lib/Release/*.lib)

    # Currently no dynamically linked libraries used, if they ever are used this will be needed.
    # FILE(GLOB EXT_DLL  ${DEPENDENCY_DIR}/bin/Release/*.dll)
    # FILE(COPY ${EXT_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
endif()

# Link lib files to project
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXT_LIBS})

# Add all includes from the dependencies folder
target_include_directories(${PROJECT_NAME} PUBLIC "${DEPENDENCY_DIR}/include")

# Add external code subdirectory files to the project
add_subdirectory("${PROJECT_SOURCE_DIR}/External")

# Add NativeFileDialog-extended as a CMAKE subdir and link it
add_subdirectory(${DEPENDENCY_DIR}/proj/nativefiledialog-extended)
target_link_libraries(${PROJECT_NAME} PRIVATE nfd)

# Add CSVParser as a CMAKE subdir and link it
add_subdirectory(${DEPENDENCY_DIR}/proj/csv-parser)
target_link_libraries(${PROJECT_NAME} PRIVATE csv)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include OpenGL include dirs
include_directories(${OPENGL_INCLUDE_DIRS})

# Link OpenGL libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

# Precompiled header configurations:

# Include the precompiled header include.h
target_precompile_headers(${PROJECT_NAME} PRIVATE [["include.h"]])

