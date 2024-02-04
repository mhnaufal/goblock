#include "GameVictoryScene.h"

void goblock::game_victory::GameVictoryScene::show_scene(std::vector<Texture2D> textures)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), goblock::setup::GOBLOCK_PINK);
    DrawText("Victory", GetScreenWidth() / 4, GetScreenHeight() / 4, 130, GREEN);
    DrawText("Press ESCAPE to back to Main Menu", GetScreenWidth() / 4, 400, 30, goblock::setup::GOBLOCK_RED2);
    DrawText("Press ENTER to go to the NEXT LEVEL!", GetScreenWidth() / 4, 500, 30, BLACK);
    DrawText("I LOVE YOU, IFA <3", GetScreenWidth() / 9, GetScreenHeight() - 200, 90, PINK);

    DrawTexture(textures[0], 10, 10, WHITE);
    DrawTexture(textures[1], GetScreenWidth() - 300, 10, WHITE);
}
