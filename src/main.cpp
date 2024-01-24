// goblock
#include "Component.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "GameVictoryScene.h"
#include "Setup.h"

int main()
{
    TraceLog(LOG_INFO, "Starting GoBlock...");
    SetTraceLogLevel(LOG_NONE);

    // Initialize world, entity, object, etc
    flecs::world game_world{};
    flecs::entity ball{};
    flecs::entity player{};
    std::vector<flecs::entity> blocks{(unsigned)goblock::setup::BLOCK_COUNT};
    goblock::game::GameScene::init(game_world, ball, player, blocks);

    // Start the game process
    InitWindow(goblock::setup::SCREEN_WIDTH, goblock::setup::SCREEN_HEIGHT, goblock::setup::GAME_NAME.c_str());
    InitAudioDevice();

    Music music = LoadMusicStream("../assets/audio/game.mp3");
    Music music_menu = LoadMusicStream("../assets/audio/menu.mp3");
    Sound sound_block = LoadSound("../assets/audio/block.mp3");
    Sound sound_win = LoadSound("../assets/audio/victory.mp3");
    Sound sound_lose = LoadSound("../assets/audio/lose.mp3");

    std::vector musics{music, music_menu};

    SetMusicVolume(music, 0.3);
    SetMusicVolume(music, 0.9);
    SetSoundVolume(sound_block, 0.8);
    SetSoundVolume(sound_win, 1.0);
    SetSoundVolume(sound_lose, 0.5);

    SetTargetFPS(60);
    SetExitKey(-1);

    goblock::setup::game_screen = goblock::setup::GameScreen::MAIN_MENU;

    while (!WindowShouldClose() && goblock::setup::game_screen != goblock::setup::GameScreen::GAME_END) {
        /// BALL
        const auto* position_ball = ball.get<goblock::component::Position>();
        const auto* radius_ball = ball.get<goblock::component::SizeCircle>();
        const auto* velocity_ball = ball.get<goblock::component::Velocity>();
        const auto* direction_ball = ball.get<goblock::component::Direction>();

        /// PLAYER
        const auto* position_player = player.get<goblock::component::Position>();
        const auto* size_player = player.get<goblock::component::SizeRectangle>();
        const auto* velocity_player = player.get<goblock::component::Velocity>();

        /// BLOCKS
        auto* position_block = blocks[0].get<goblock::component::Position>();
        auto* size_block = blocks[0].get<goblock::component::SizeRectangle>();
        for (auto& block : blocks) {
            position_block = block.get<goblock::component::Position>();
            size_block = block.get<goblock::component::SizeRectangle>();
            goblock::game::GameScene::collision_block(
                ball, block, position_block, size_block, position_ball, radius_ball, velocity_ball, direction_ball);
        }

        switch (goblock::setup::game_screen) {
        case goblock::setup::GameScreen::MAIN_MENU: {
            if (IsKeyPressed(KEY_ENTER)) {
                goblock::setup::game_screen = goblock::setup::GameScreen::GAME;
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                goblock::setup::game_screen = goblock::setup::GameScreen::GAME_END;
            }
            break;
        }
        case goblock::setup::GameScreen::GAME_OVER: {
            if (IsKeyPressed(KEY_ESCAPE)) {
                goblock::setup::game_screen = goblock::setup::GameScreen::MAIN_MENU;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                ball.set<goblock::component::Position>(
                    {static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2,
                     static_cast<float>(goblock::setup::SCREEN_HEIGHT) / 6});
                ball.set<goblock::component::Velocity>({goblock::setup::BALL_SPEED, goblock::setup::BALL_SPEED});

                goblock::setup::BLOCK_COUNT = 8;
                for (auto& block : blocks) { block.set<goblock::component::Destroyed>({false}); }

                goblock::setup::game_screen = goblock::setup::GameScreen::GAME;
            }
            break;
        }
        case goblock::setup::GameScreen::GAME_VICTORY: {
            if (IsKeyPressed(KEY_ESCAPE)) {
                goblock::setup::game_screen = goblock::setup::GameScreen::MAIN_MENU;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                ball.set<goblock::component::Position>(
                    {static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2,
                     static_cast<float>(goblock::setup::SCREEN_HEIGHT) / 6});
                ball.set<goblock::component::Velocity>({goblock::setup::BALL_SPEED, goblock::setup::BALL_SPEED});

                goblock::setup::BLOCK_COUNT = 8;
                for (auto& block : blocks) { block.set<goblock::component::Destroyed>({false}); }

                goblock::setup::game_screen = goblock::setup::GameScreen::GAME;
            }
            break;
        }
        case goblock::setup::GameScreen::PAUSE: {
            TraceLog(LOG_INFO, "PAUSE");
            break;
        }
        case goblock::setup::GameScreen::GAME_END: {
            TraceLog(LOG_INFO, "GAME_END");
            break;
        }
        case goblock::setup::GameScreen::GAME: {
            goblock::game::GameScene::movement_player(player, position_player, velocity_player);
            goblock::game::GameScene::movement_ball(ball, position_ball, velocity_ball, direction_ball);

            goblock::game::GameScene::collision_player(player, position_player, size_player);
            goblock::game::GameScene::collision_ball(ball, position_ball, radius_ball, velocity_ball, direction_ball);

            /// Ball and player collision
            goblock::game::GameScene::player_ball_collision(
                ball,
                position_ball,
                radius_ball,
                velocity_ball,
                direction_ball,
                position_player,
                size_player,
                sound_block);

            /// Ball out of screen
            goblock::game::GameScene::ball_out(position_ball, radius_ball, sound_lose, goblock::setup::game_screen);

            /// Winning check
            goblock::game::GameScene::winning_check(sound_win, goblock::setup::game_screen);
            break;
        }
        default:
            break;
        }

        BeginDrawing();
        ClearBackground(goblock::setup::GOBLOCK_GRAY);

        switch (goblock::setup::game_screen) {
        case goblock::setup::GameScreen::MAIN_MENU: {
            UpdateMusicStream(music_menu);
            PlayMusicStream(music_menu);

            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            DrawText("GOBLOCK", 40, 40, 120, RED);
            DrawText("A game by mhnpratama", 40, 170, 30, DARKBLUE);
            DrawText("Press ENTER to start", 40, GetScreenHeight() - 120, 40, BLACK);
            DrawText("Press Esc to quit", 40, GetScreenHeight() - 70, 20, DARKGRAY);
            break;
        }
        case goblock::setup::GameScreen::GAME_OVER: {
            goblock::game_over::GameOverScene::show_scene();
            break;
        }
        case goblock::setup::GameScreen::GAME_VICTORY: {
            goblock::game_victory::GameVictoryScene::show_scene();
            break;
        }
        case goblock::setup::GameScreen::PAUSE: {
            TraceLog(LOG_INFO, "PAUSE");
            break;
        }
        case goblock::setup::GameScreen::GAME_END: {
            TraceLog(LOG_INFO, "GAME_END");
            break;
        }
        case goblock::setup::GameScreen::GAME: {
            UpdateMusicStream(music);
            PlayMusicStream(music);

            goblock::game::GameScene::render_ball(position_ball, radius_ball, goblock::setup::GOBLOCK_WHITE);
            goblock::game::GameScene::render_player(position_player, size_player, goblock::setup::GOBLOCK_BLUE);

            for (auto& block : blocks) {
                position_block = block.get<goblock::component::Position>();
                size_block = block.get<goblock::component::SizeRectangle>();
                goblock::game::GameScene::render_blocks(
                    block, position_block, size_block, goblock::setup::GOBLOCK_GREEN);
            }
            break;
        }
        default:
            break;
        }

        EndDrawing();
    }

    // Cleanup
    goblock::game::GameScene::cleanup(musics);

    return 0;
}
