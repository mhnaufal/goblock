#pragma once

// Third-party
#include <flecs.h>
#include <raylib.h>

// STL
#include <cassert>
#include <cstring>
#include <iostream>

namespace goblock {

/******************
 * Global Setup
 ******************/
namespace setup {

static const std::string GAME_NAME = "GoBlock";

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 800;

enum class GameScreen : int32_t {
    MAIN_MENU = 0,
    GAME = 1,
    GAME_OVER = 2,
    PAUSE = 3
};

static GameScreen game_screen = GameScreen::MAIN_MENU;
} // namespace setup

/******************
 * Component
 ******************/
namespace component {

struct Position {
public:
    int x{};
    int y{};
};

struct Velocity {
public:
    int x{};
    int y{};
};

struct SizeRectangle {
public:
    int width{};
    int height{};
};

struct SizeCircle {
public:
    int radius{};
};
} // namespace component

/******************
 * System
 ******************/
namespace system {

flecs::entity create_object(flecs::world& game_world, const std::string& name,
        const component::Position& pos, const component::SizeRectangle& size,
        const component::Velocity& vel);

flecs::entity create_object(flecs::world& game_world, const std::string& name,
        const component::Position& pos, const component::SizeCircle& size,
        const component::Velocity& vel);
} // namespace system
} // namespace goblock
