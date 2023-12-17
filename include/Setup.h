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

enum class GameScreen : uint8_t {
    MAIN_MENU = 0,
    GAME = 1,
    GAME_OVER = 2,
    PAUSE = 3
};

static GameScreen game_screen = GameScreen::MAIN_MENU;

static const float GRAVITY{0.7};
} // namespace setup

} // namespace goblock
