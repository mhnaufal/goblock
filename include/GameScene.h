#pragma once

// goblock
#include "Component.h"
#include "Setup.h"
#include "System.h"

namespace goblock::game {

class GameScene {
public:
    static void init(flecs::world& game_world, flecs::entity& ball, flecs::entity& player);

    /// BALL
    static void render_ball(
        const goblock::component::Position* position_ball,
        const goblock::component::SizeCircle* radius_ball,
        Color& color);

    static void movement_ball(
        flecs::entity& ball,
        const goblock::component::Position* position_ball,
        const goblock::component::Velocity* velocity_ball);

    static void collision_ball(
        flecs::entity& ball,
        const goblock::component::Position* position_ball,
        const goblock::component::SizeCircle* radius_ball,
        const goblock::component::Velocity* velocity_ball);

    /// PLAYER
    static void render_player(
        const goblock::component::Position* position_player,
        const goblock::component::SizeRectangle* size_player,
        Color& color);

    static void movement_player(
        flecs::entity& player,
        const goblock::component::Position* position_player,
        const goblock::component::Velocity* velocity_player);

    static void collision_player(
        flecs::entity& player,
        const goblock::component::Position* position_player,
        const goblock::component::SizeRectangle* size_player,
        const goblock::component::Velocity* velocity_player);

    static void cleanup();

private:
};

} // namespace goblock::game
