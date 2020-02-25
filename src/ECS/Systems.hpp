#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "ECS.hpp"
#include "Components.hpp"

class MovementSystem: public System {
public:
    MovementSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

class DrawSystem: public System {
public:
    DrawSystem(Manager* manager);
    void update() override;
    void draw() override;
};

#endif