cmake_minimum_required (VERSION 3.20)

find_package(Doxygen)

if(DOXYGEN_FOUND)
	message(STATUS "Doxygen found, generating documentation")
else()
	message(STATUS "Doxygen not found, skipping documentation generation")
endif()

set(PROJECT_NAME "IC-GoD-DataEditorTool")
set(PROJECT_BRIEF "CSV data editing tool for GoD romhacking")
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(FILES_DIR ${PROJECT_SOURCE_DIR}/DataEditorTool)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Generate Doxygen documentation"
)