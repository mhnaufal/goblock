#pragma once

#include <iostream>
#include <raylib.h>
#include <flecs.h>
#include <assert.h>
#include <string.h>

static const std::string GAME_NAME = "GoBlock";

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 800;

enum class GameScreen : int32_t
{
    MAIN_MENU = 0,
    GAME = 1,
    GAME_OVER = 2,
    PAUSE = 3
};
GameScreen game_screen = GameScreen::MAIN_MENU;
