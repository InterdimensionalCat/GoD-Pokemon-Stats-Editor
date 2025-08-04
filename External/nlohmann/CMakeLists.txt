cmake_minimum_required (VERSION 3.20)

# Add nlohmann json.hpp file to project
target_sources(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/json.hpp")

# Disable precompiled header in json.hpp
set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/json.hpp" PROPERTIES SKIP_PRECOMPILE_HEADERS ON)