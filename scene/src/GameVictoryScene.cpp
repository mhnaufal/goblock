#include "GameVictoryScene.h"

void goblock::game_victory::GameVictoryScene::show_scene()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
    DrawText("Victory", GetScreenWidth() / 4, GetScreenHeight() / 4, 130, GREEN);
    DrawText("Press ESCAPE to back to Main Menu", GetScreenWidth() / 4, 400, 30, RED);
    DrawText("Press ENTER to play again", GetScreenWidth() / 4, 500, 30, ORANGE);
    DrawText("I LOVE YOU, IFA <3", GetScreenWidth() / 8, GetScreenHeight() - 200, 90, PINK);
}
