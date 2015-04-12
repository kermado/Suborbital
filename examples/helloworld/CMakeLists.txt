# Project Name.
project(HelloWorld)

# Include headers.
include_directories(${PROJECT_SOURCE_DIR})

# Source files.
set(SOURCE_FILES
    main.cpp
)

# Create executable.
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link the Suborbital library with the executable.
target_link_libraries(${PROJECT_NAME} Suborbital)