#pragma once

namespace goblock
{
/******************
 * Component
 ******************/
namespace component {

struct Position {
public:
    int x{};
    int y{};
};

struct Velocity {
public:
    int x{};
    int y{};
};

struct SizeRectangle {
public:
    int width{};
    int height{};
};

struct SizeCircle {
public:
    int radius{};
};
} // namespace component
}