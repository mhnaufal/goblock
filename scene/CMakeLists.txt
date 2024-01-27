add_library(
        scene
        src/GameScene.cpp
        src/GameOverScene.cpp
        src/GameVictoryScene.cpp
)

target_include_directories(scene PUBLIC include ${CMAKE_SOURCE_DIR}/app ${CMAKE_SOURCE_DIR}/system/include)

#######################
# Raylib
#######################
find_package(raylib REQUIRED)
target_link_libraries(scene PUBLIC raylib)
target_include_directories(scene PUBLIC ${raylib_INCLUDE_DIRS})

#######################
# Flecs
#######################
find_package(flecs REQUIRED)
target_link_libraries(scene PUBLIC flecs::flecs_static)
target_include_directories(scene PUBLIC ${flecs_INCLUDE_DIRS})
