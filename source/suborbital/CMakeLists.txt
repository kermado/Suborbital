# Library name
set(LIBRARY_NAME Suborbital)

# Set project path variables.
SET(INC_ROOT ${PROJECT_SOURCE_DIR}/include/subrbital)
SET(SRC_ROOT ${PROJECT_SOURCE_DIR}/source/suborbital)
SET(SWIG_ROOT ${PROJECT_SOURCE_DIR}/swig/suborbital)

# Source files.
set(SOURCE_FILES
	${SRC_ROOT}/watch_ptr.cpp
	${SRC_ROOT}/Watchable.cpp
	${SRC_ROOT}/Entity.cpp
	${SRC_ROOT}/ScriptInterpreter.cpp
	${SRC_ROOT}/PythonInterpreter.cpp
	${SRC_ROOT}/component/Component.cpp
	${SRC_ROOT}/component/PythonAttribute.cpp
	${SRC_ROOT}/component/Attribute.cpp
	${SRC_ROOT}/component/Behaviour.cpp
	${SRC_ROOT}/component/PythonBehaviour.cpp
	${SRC_ROOT}/component/ComponentRegistry.cpp
	${SRC_ROOT}/component/ExampleAttribute.cpp
)

# Create a shared library.
add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES})

# Python.
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
target_link_libraries(${LIBRARY_NAME} ${PYTHON_LIBRARIES})

# SWIG.
set(SWIG_LIBRARY_NAME suborbital)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_SWIG_FLAGS "")

#if(NOT EXISTS SwigRuntime.h)
	execute_process(COMMAND ${SWIG_EXECUTABLE} -python -c++ -external-runtime SwigRuntime.h)
#endif()

set_source_files_properties(${SWIG_ROOT}/Suborbital.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${SWIG_ROOT}/Suborbital.i PROPERTIES SWIG_FLAGS "-I${PROJECT_SOURCE_DIR}/swig")
swig_add_module(${SWIG_LIBRARY_NAME} python ${SWIG_ROOT}/Suborbital.i ${SOURCE_FILES})
swig_link_libraries(${SWIG_LIBRARY_NAME} ${PYTHON_LIBRARIES})

# Install.
INSTALL(TARGETS ${LIBRARY_NAME} DESTINATION lib)
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/include
		DESTINATION .
		PATTERN ".svn" EXCLUDE
		PATTERN ".DS_Store" EXCLUDE)