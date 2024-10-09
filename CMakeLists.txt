cmake_minimum_required (VERSION 3.20)

project ("GoD-Pokemon-Stats-Editor")

add_compile_options(/Zc:wchar_t-)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(IMGUI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/imgui)

FILE(GLOB IMGUI_CPP_FILES ${IMGUI_SOURCE_DIR}/*.cpp)
FILE(GLOB IMGUI_H_FILES ${IMGUI_SOURCE_DIR}/*.h)

FILE(GLOB IMGUI_BACKEND_FILES ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.h ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.h ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
FILE(GLOB IMGUI_DEBUG_FILES ${IMGUI_SOURCE_DIR}/misc/debuggers/imgui.natvis ${IMGUI_SOURCE_DIR}/misc/debuggers/imgui.natstepfilter ${IMGUI_SOURCE_DIR}/misc/cpp/imgui_stdlib.* ${IMGUI_SOURCE_DIR}/misc/freetype/imgui_freetype.*)

add_executable (GoD-Pokemon-Stats-Editor "src/GoD-UI-Windows.cpp" "src/GoD-UI-Windows.h" ${PROJECT_SOURCE_DIR}/src/glad/glad.c ${IMGUI_CPP_FILES} ${IMGUI_H_FILES} ${IMGUI_BACKEND_FILES} ${IMGUI_DEBUG_FILES} "src/nlohmann/json.hpp" "src/CSV Data/Pokemon Stats.h" "src/CSV Data/Pokemon Stats.cpp" "src/CSV Data/Moves.h" "src/CSV Data/Moves.cpp" "src/UiSections/UiSubsections/IdentificationInfo.h" "src/UiSections/PokemonList.h" "src/UiSections/PokemonList.cpp" "src/UiSections/UiSubsections/IdentificationInfo.cpp" "src/UiSections/UiSubsections/TypeInfo.h" "src/UiSections/UiSubsections/TypeInfo.cpp" "src/CSV Data/Types.h" "src/CSV Data/Types.cpp" "src/CSV Data/Csv Data.h" "src/CSV Data/Csv Data.cpp" "src/UiSections/UiSection.h" "src/UiSections/UiSection.cpp" "src/CSV Data/Abilities.h" "src/CSV Data/Abilities.cpp" "src/UiSections/UiSubsections/AbilityInfo.h" "src/UiSections/UiSubsections/AbilityInfo.cpp" "src/CSV Data/Items.h" "src/CSV Data/Items.cpp" "src/UiSections/UiSubsections/WildItemInfo.h" "src/UiSections/UiSubsections/WildItemInfo.cpp" "src/UiSections/BaseStats.h" "src/UiSections/BaseStats.cpp" "src/UiSections/UiSubsections/EVYieldInfo.h" "src/UiSections/UiSubsections/EVYieldInfo.cpp" "src/UiSections/UiSubsections/LevelUpMoves.h" "src/UiSections/UiSubsections/LevelUpMoves.cpp" "src/Util/FilterableComboBox.h" "src/Util/FilterableComboBox.cpp" "src/UiSections/TeachableMoveInfo.h" "src/UiSections/TeachableMoveInfo.cpp" "src/UiSections/EvolutionInfo.h" "src/UiSections/EvolutionInfo.cpp" "src/UiSections/UiSubsections/MiscInfo.h" "src/UiSections/UiSubsections/MiscInfo.cpp"   "src/Command/Command.h" "src/Command/Command.cpp" "src/Command/SwitchActivePokemon.h" "src/Command/SwitchActivePokemon.cpp" "src/UiSections/UiSubsections/Egg Moves.h" "src/UiSections/UiSubsections/Egg Moves.cpp" "src/Command/ModifyValue.h" "src/Command/ModifyValue.cpp"   "src/Command/ModifyHappiness.h" "src/Command/ModifyHappiness.cpp" "src/Command/SwapMoves.h" "src/Command/SwapMoves.cpp"   "src/Util/UnsavedProgressModal.h" "src/Util/UnsavedProgressModal.cpp"     "src/UiSections/SpeciesInfo.h" "src/UiSections/SpeciesInfo.cpp" "src/UiSections/UiSubsections/UiSubsection.h" "src/UiSections/UiSubsections/UiSubsection.cpp" "src/stb_image/stb_image.h"  "src/Util/TextureLoader.h" "src/Util/TextureLoader.cpp" "src/Util/ItemSizeUtils.h" "src/Util/ItemSizeUtils.cpp" "src/UiSections/LearnedMoves.h" "src/UiSections/LearnedMoves.cpp" "src/Settings/FontSettings.h" "src/Settings/FontSettings.cpp" "src/Settings/Settings.h" "src/Settings/Settings.cpp" "src/Settings/LayoutSettings.h" "src/Settings/LayoutSettings.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GoD-Pokemon-Stats-Editor PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
set(DEPENDENCY_DIR "${PROJECT_SOURCE_DIR}/Dependencies")

# Find all static libraries in dependencies and copy it to the output dir, and link each
if(CMAKE_BUILD_TYPE MATCHES Debug)
    FILE(GLOB EXT_LIBS ${DEPENDENCY_DIR}/lib/Debug/*.lib)
    #FILE(COPY ${EXT_LIBS} DESTINATION "${CMAKE_BINARY_DIR}")
else()
    FILE(GLOB EXT_LIBS ${DEPENDENCY_DIR}/lib/Release/*.lib)
    #FILE(COPY ${EXT_LIBS} DESTINATION "${CMAKE_BINARY_DIR}")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(MESSAGE_QUIET ON)
    message(STATUS "Building on debug mode; debug_mode defined")
    set(MESSAGE_QUIET OFF)
    add_compile_definitions(debug_mode)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXT_LIBS})

# include project src root dir
include_directories(${PROJECT_SOURCE_DIR}/src/)

# add all includes from the dependencies folder
include_directories(${DEPENDENCY_DIR}/include)

# include Imgui directory
include_directories(${IMGUI_SOURCE_DIR})

# include Imgui backend directory
include_directories(${PROJECT_SOURCE_DIR}/src/imgui/backends)

# Add NativeFileDialog-extended as a CMAKE subdir and link it
add_subdirectory(${DEPENDENCY_DIR}/proj/nativefiledialog-extended)
target_link_libraries(${PROJECT_NAME} PRIVATE nfd)

# Add CSVParser as a CMAKE subdir and link it
add_subdirectory(${DEPENDENCY_DIR}/proj/csv-parser)
target_link_libraries(${PROJECT_NAME} PRIVATE csv)

set(RESOURCE_DIR "${PROJECT_SOURCE_DIR}/Resources")

#adds resource files to the build
FILE(COPY ${RESOURCE_DIR} DESTINATION "${CMAKE_BINARY_DIR}")

# find OpenGL, include it, and include it
#find_package(OpenGL REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
