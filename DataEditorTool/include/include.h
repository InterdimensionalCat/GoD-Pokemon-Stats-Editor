/*****************************************************************//**
 * \file   include.h
 * \brief  Precompiled header file with common includes and macro definitions
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

/**
 * STL includes.
 */
#include <algorithm>
#include <any>
#include <array>
#include <bitset>
#include <chrono>
#include <concepts>
#include <deque>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <initializer_list>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

namespace fs = std::filesystem;

/**
 * nlohman::json includes
 * nlohman::json is a json library that allows us to use jsons as first class container objects.
 */
#include <nlohmann\json.hpp>

using json = nlohmann::json;

/**
 * GLFW includes.
 * GLFW is a cross platform API for creating and managing windows, and handling input.
 * 
 * NOTE: these should no longer be included in the PCH as we are trying to contain
 * backend code to Context objects in case a backend change is needed in the future.
 * See WindowContext.h/cpp for more info
 */
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//#include <glad/glad.h>

/**
 * imgui includes
 * imgui is a GUI library.
 */
#include "Contexts/CustomImConfig.h" // Custom config for ImGui

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"

/**
 * TODO: Ideally these includes should only be needed in the Window/Gui context cpp files.
 * However, there is some linking issue that occurs if they are not included here, I suspect
 * its due to some of the imgui includes below needing access to these backends.
 */
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

/** Helper functions that allow for stl containers to be used in ImGui functions. */
#include "imgui/misc/cpp/imgui_stdlib.h"

/** Some ImGui functionality is deliberately hidden in their internal header for some reason. */
#include "imgui/imgui_internal.h"

/**
 * include ImGuiNotify.
 * ImGuiNotify is a toast notification library for ImGui.
 */
#include "imgui/backends/ImGuiNotify.hpp"

/**
 * Native File Dialogue includes.
 * Native File Dialogue is a cross platform library for opening a file selection dialogue box.
 */
#include <nfd.hpp>

/**
 * csv-parser includes.
 * csv-parser is a csv parsing library.
 */
#include <csv.hpp>

/**
 * spdlog includes.
 * spdlog is a logging library.
 */
#include "spdlog/spdlog.h"

/**
 * Project includes.
 * Some project headers, like Logger.h,
 * are used so frequently that they might as well
 * be included here
 */
#include "Logging/Logger.h"
#include "MainEditor/DataEditorInstance.h"

/**
 * Changes to dependancies:
 * 
 * csv_writer.hpp, line 318:
 * IC_CHANGE: disable quoting when writing to a CSV
 * 
 * ImGuiNotify.hpp, line 474:
 * IC_CHANGE: Insert notifications at the front of the array
 * so they are rendered most to least recent.
 */
