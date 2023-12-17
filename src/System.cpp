#include "System.h"

#include "Setup.h"

namespace goblock {
namespace system {

flecs::entity create_object(flecs::world& game_world, const std::string& name,
        const goblock::component::Position& pos,
        const goblock::component::SizeRectangle& size,
        const goblock::component::Velocity& vel) {
    auto object = game_world.entity(name.c_str());
    object.set<goblock::component::Position>({pos.x, pos.y});
    object.set<goblock::component::SizeRectangle>({size.width, size.height});
    object.set<goblock::component::Velocity>({vel.x, vel.y});
    return object;
}

flecs::entity create_object(flecs::world& game_world, const std::string& name,
        const goblock::component::Position& pos,
        const goblock::component::SizeCircle& size,
        const goblock::component::Velocity& vel) {
    auto object = game_world.entity(name.c_str());
    object.set<goblock::component::Position>({pos.x, pos.y});
    object.set<goblock::component::SizeCircle>({size.radius});
    object.set<goblock::component::Velocity>({vel.x, vel.y});
    return object;
}

} // namespace system
} // namespace goblock
