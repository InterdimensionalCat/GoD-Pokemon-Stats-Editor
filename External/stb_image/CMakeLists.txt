cmake_minimum_required (VERSION 3.20)

# Add stb_image.h file to project
target_sources(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h")

# Disable precompiled header in stb_image.h
set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h" PROPERTIES SKIP_PRECOMPILE_HEADERS ON)