# Library name
set(LIBRARY_NAME Suborbital)

# Set project path variables.
set(INC_ROOT ${PROJECT_SOURCE_DIR}/include/suborbital)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/source/suborbital)
set(SWIG_ROOT ${PROJECT_SOURCE_DIR}/swig/suborbital)

# Source files.
set(SOURCE_FILES
	${SRC_ROOT}/WatchPtr.cpp
	${SRC_ROOT}/Watchable.cpp

	${SRC_ROOT}/Entity.cpp
	${SRC_ROOT}/EntitySet.cpp
	${SRC_ROOT}/EntityManager.cpp

	${SRC_ROOT}/ScriptInterpreter.cpp
	${SRC_ROOT}/PythonInterpreter.cpp

	${SRC_ROOT}/scene/SceneStack.cpp
	${SRC_ROOT}/scene/Scene.cpp
	${SRC_ROOT}/scene/PythonScene.cpp

	${SRC_ROOT}/system/System.cpp
	${SRC_ROOT}/system/PythonSystem.cpp
	${SRC_ROOT}/system/SystemRegistry.cpp

	${SRC_ROOT}/component/Component.cpp
	${SRC_ROOT}/component/Attribute.cpp
	${SRC_ROOT}/component/Behaviour.cpp
	${SRC_ROOT}/component/PythonAttribute.cpp
	${SRC_ROOT}/component/PythonBehaviour.cpp
	${SRC_ROOT}/component/ComponentRegistry.cpp

	${SRC_ROOT}/event/EventDispatcher.cpp
	${SRC_ROOT}/event/EventSubscription.cpp
	${SRC_ROOT}/event/Event.cpp
	${SRC_ROOT}/event/PythonEvent.cpp
	${SRC_ROOT}/event/EventCallbackBase.cpp
	${SRC_ROOT}/event/PythonEventCallback.cpp
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

if(NOT EXISTS SwigRuntime.h)
	execute_process(COMMAND ${SWIG_EXECUTABLE} -python -c++ -external-runtime SwigRuntime.h)
endif()

set_source_files_properties(${SWIG_ROOT}/Module.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${SWIG_ROOT}/Module.i PROPERTIES SWIG_FLAGS "-I${PROJECT_SOURCE_DIR}/swig")
swig_add_module(${SWIG_LIBRARY_NAME} python ${SWIG_ROOT}/Module.i ${SOURCE_FILES})
swig_link_libraries(${SWIG_LIBRARY_NAME} ${PYTHON_LIBRARIES})

# Install.
install(TARGETS ${LIBRARY_NAME} DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
		DESTINATION .
		PATTERN ".svn" EXCLUDE
		PATTERN ".DS_Store" EXCLUDE)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/swig/suborbital/
		DESTINATION include/suborbital
		PATTERN ".svn" EXCLUDE
		PATTERN ".DS_Store" EXCLUDE)