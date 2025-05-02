cmake_minimum_required(VERSION 3.31)
project(RaylibSnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "-static -static-libgcc -static-libstdc++")

include(FetchContent)

# Fetch raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

# Fetch glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1  # or the version you want
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glm)

# Fetch imgui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.9
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(imgui)

# Fetch rlImGui (raylib ImGui wrapper)
FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG main
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(rlimgui)

# Gather all source files from src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Hide console window on Windows if the build type is Release
if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Gather all source files of libraries
file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
file(GLOB RLIMGUI_SOURCES ${rlimgui_SOURCE_DIR}/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_SOURCES} ${RLIMGUI_SOURCES})

# Include raylib headers, and the src directory
target_include_directories(${PROJECT_NAME} PRIVATE
        ${raylib_SOURCE_DIR}/src
        ${raylib_SOURCE_DIR}/examples
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${glm_SOURCE_DIR}
        ${rlimgui_SOURCE_DIR} # Include rlImGui headers (the name is lowercase)
        ${imgui_SOURCE_DIR} # Include ImGui headers
        ${imgui_SOURCE_DIR}/backends
)

# Print rlimgui_SOURCE_DIR
message(STATUS "rlimgui_SOURCE_DIR: ${rlimgui_SOURCE_DIR}")

# Link raylib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Copy assets directory
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)