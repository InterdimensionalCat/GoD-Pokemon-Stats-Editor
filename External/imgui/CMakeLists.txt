cmake_minimum_required (VERSION 3.20)

set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add all imgui cpp files to the build
FILE(GLOB IMGUI_CPP_FILES ${IMGUI_SOURCE_DIR}/*.cpp)

# Add all imgui h files to the build
FILE(GLOB IMGUI_H_FILES ${IMGUI_SOURCE_DIR}/*.h)

# Add the needed imgui backend files to the build (Using the glfw/opengl3 backends)
FILE(GLOB IMGUI_BACKEND_FILES
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.h
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# Add the needed imgui debug files to the build
FILE(GLOB IMGUI_DEBUG_FILES
    ${IMGUI_SOURCE_DIR}/misc/debuggers/imgui.natvis
    ${IMGUI_SOURCE_DIR}/misc/debuggers/imgui.natstepfilter
    ${IMGUI_SOURCE_DIR}/misc/cpp/imgui_stdlib.*
    ${IMGUI_SOURCE_DIR}/misc/freetype/imgui_freetype.*)

# Add the files globed above to the project
target_sources(${PROJECT_NAME} PUBLIC ${IMGUI_CPP_FILES} ${IMGUI_H_FILES} ${IMGUI_BACKEND_FILES} ${IMGUI_DEBUG_FILES})

# Add the imgui directory to includes
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_SOURCE_DIR})

# Add the imgui backend directory to includes
target_include_directories(${PROJECT_NAME} PUBLIC "${IMGUI_SOURCE_DIR}/backends")

# We don't want the precompiled header to be required for imgui files, so turn that off.
set_source_files_properties(${IMGUI_CPP_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(${IMGUI_H_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(${IMGUI_BACKEND_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(${IMGUI_DEBUG_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
