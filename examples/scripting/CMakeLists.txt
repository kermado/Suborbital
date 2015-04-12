# Project Name.
project(ScriptingExample)

# Set project path variables.
SET(SWIG_ROOT ${PROJECT_SOURCE_DIR}/swig)

# Include headers.
include_directories(${PROJECT_SOURCE_DIR})

# Source files.
set(SOURCE_FILES
    main.cpp
    ExampleAttribute.cpp
)

# Create executable.
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Python.
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
target_link_libraries(ScriptingExample ${PYTHON_LIBRARIES})

# SWIG.
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_SWIG_FLAGS "")

# Build our own "scripting" module that can be imported inside of Python scripts.
# This module contains all of our C++ defined components that we want to expose to Python.
# Note that we need to link this module with both the Python and Suborbital libraries.
set(SWIG_LIBRARY_NAME scripting)
set_source_files_properties(${SWIG_ROOT}/Scripting.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${SWIG_ROOT}/Scripting.i PROPERTIES SWIG_FLAGS "-I${SWIG_ROOT}")
swig_add_module(${SWIG_LIBRARY_NAME} python ${SWIG_ROOT}/Scripting.i ${SOURCE_FILES})
swig_link_libraries(${SWIG_LIBRARY_NAME} ${PYTHON_LIBRARIES})
swig_link_libraries(${SWIG_LIBRARY_NAME} Suborbital)

# Link the Suborbital library with the executable.
target_link_libraries(${PROJECT_NAME} Suborbital)