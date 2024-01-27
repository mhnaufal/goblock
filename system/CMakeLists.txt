add_library(
        system
        src/System.cpp
)

target_include_directories(system PUBLIC include ${CMAKE_SOURCE_DIR}/app)

#######################
# Raylib
#######################
find_package(raylib REQUIRED)
target_link_libraries(system PUBLIC raylib)
target_include_directories(system PUBLIC ${raylib_INCLUDE_DIRS})

#######################
# Flecs
#######################
find_package(flecs REQUIRED)
target_link_libraries(system PUBLIC flecs::flecs_static)
target_include_directories(system PUBLIC ${flecs_INCLUDE_DIRS})
