cmake_minimum_required (VERSION 3.20)

# Add nlohmann json files to the project
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/nlohmann")

# Add glad files to the project
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glad")

# Add imgui files to the project
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/imgui")

# Add stb_image files to the project
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/stb_image")

# Add the external directory as an include dir
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/External")
