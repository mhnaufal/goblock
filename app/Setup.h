#pragma once

// Third-party
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>

// STL
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

/******************
 * Global Setup
 ******************/
namespace goblock::setup {

static const std::string GAME_NAME = "GoBlock";

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 800;

enum class GameScreen : uint8_t { MAIN_MENU = 0, GAME = 1, GAME_OVER = 2, PAUSE = 3, GAME_VICTORY = 4, GAME_END = 5 };
enum class LevelScreen : uint8_t { LEVEL_1 = 1, LEVEL_2 = 2 };

static GameScreen game_screen = GameScreen::MAIN_MENU;
static LevelScreen level_screen = LevelScreen::LEVEL_1;

static const float GRAVITY{0.4f};
static const float BALL_SPEED{8};

extern int BLOCK_COUNT;
extern int SCORE;
extern int LIVE;

static Color GOBLOCK_GRAY{21, 27, 45};
static Color GOBLOCK_WHITE{255, 251, 195, 255};
static Color GOBLOCK_BLUE{131, 158, 238, 255};
static Color GOBLOCK_GREEN{94, 247, 109, 255};
static Color GOBLOCK_RED{255, 90, 90, 255};

} // namespace goblock::setup
