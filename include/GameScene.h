#pragma once

// goblock
#include "Component.h"
#include "Setup.h"
#include "System.h"

namespace goblock {
namespace game {

class GameScene {
public:
    void init(flecs::world& game_world, flecs::entity& ball, flecs::entity& player);
    void cleanup();
private:

};

} // namespace game
} // namespace goblock