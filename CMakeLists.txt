cmake_minimum_required(VERSION 3.22)
project(CommandCheatsBypass LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT DEFINED MOD_ID)
    set(MOD_ID command_cheats_bypass)
endif()
if(NOT DEFINED MOD_NAME)
    set(MOD_NAME "Command Cheats Bypass")
endif()
if(NOT DEFINED MOD_AUTHOR)
    set(MOD_AUTHOR "Electrocharge")
endif()
if(NOT DEFINED MOD_VERSION)
    set(MOD_VERSION 0.1.0)
endif()
if(NOT DEFINED MOD_LIBRARY_NAME)
    set(MOD_LIBRARY_NAME command_cheats_bypass)
endif()
if(NOT DEFINED MOD_MINECRAFT_VERSIONS)
    set(MOD_MINECRAFT_VERSIONS "[]")
endif()

include(FetchContent)
FetchContent_Declare(
    preloader_android
    GIT_REPOSITORY https://github.com/LiteLDev/preloader-android.git
    GIT_TAG 0.2.2
)
FetchContent_MakeAvailable(preloader_android)

find_library(ANDROID_LOG_LIB log REQUIRED)

add_library(${MOD_LIBRARY_NAME} SHARED
    src/main.cpp
    src/mod/CommandCheatsBypass.cpp
)

target_include_directories(${MOD_LIBRARY_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${MOD_LIBRARY_NAME} PRIVATE preloader fmt::fmt ${ANDROID_LOG_LIB})

target_compile_definitions(${MOD_LIBRARY_NAME} PRIVATE
    MOD_ID="${MOD_ID}"
    MOD_VERSION="${MOD_VERSION}"
)

target_compile_options(${MOD_LIBRARY_NAME} PRIVATE
    -Oz
    -fvisibility=hidden
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/manifest.json.in
    ${CMAKE_CURRENT_BINARY_DIR}/manifest.json
    @ONLY
)

add_custom_target(levi_package ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/package/${MOD_ID}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${MOD_LIBRARY_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/package/${MOD_ID}/lib${MOD_LIBRARY_NAME}.so
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/manifest.json ${CMAKE_CURRENT_BINARY_DIR}/package/${MOD_ID}/manifest.json
    COMMAND ${CMAKE_COMMAND} -E tar ccf ${CMAKE_CURRENT_BINARY_DIR}/${MOD_ID}.levipack --format=zip ${MOD_ID}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/package
    DEPENDS ${MOD_LIBRARY_NAME}
)
