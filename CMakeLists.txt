cmake_minimum_required(VERSION 3.23)

project(
        goblock
        VERSION 1.0
        DESCRIPTION "Go-Block: A simple blocks destroyer game!"
        LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /permissive-")
endif ()

if (CMAKE_GNU_COMPILER_ID)
    set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wpedantic")
endif ()

add_subdirectory(scene)
add_subdirectory(system)

add_executable(${PROJECT_NAME} app/main.cpp app/Setup.h)

target_link_libraries(${PROJECT_NAME} PUBLIC system scene)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

#######################
# Raylib
#######################
find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_include_directories(${PROJECT_NAME} PUBLIC ${raylib_INCLUDE_DIRS})

#######################
# Flecs
#######################
find_package(flecs REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC flecs::flecs_static)
target_include_directories(${PROJECT_NAME} PUBLIC ${flecs_INCLUDE_DIRS})

#######################
# EnTT
#######################
# find_package(EnTT REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC EnTT::EnTT)
# target_include_directories(${PROJECT_NAME} PUBLIC ${EnTT_INCLUDE_DIRS})

#######################
# MSVC
#######################
if (MSVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
endif ()
