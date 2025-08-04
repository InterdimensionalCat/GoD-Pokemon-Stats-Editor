cmake_minimum_required (VERSION 3.20)

# Add glad.c file to project
target_sources(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad.cpp")

# Disable precompiled header in glad.c
set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/glad.cpp" PROPERTIES SKIP_PRECOMPILE_HEADERS ON)