#include "GameOverScene.h"

namespace goblock::game_over {

void GameOverScene::show_scene()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawText("Game Over", GetScreenWidth() / 4, GetScreenHeight() / 4, 130, RED);
    DrawText("Press ESCAPE to back to Main Menu", GetScreenWidth() / 4, 400, 30, WHITE);
    DrawText("Press ENTER to play again", GetScreenWidth() / 4, 500, 30, GREEN);
}

} // namespace goblock::game_over
