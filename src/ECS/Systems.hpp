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

class JumpSystem: public System {
public:
    JumpSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

class CollisionSystem: public System {
public:
    CollisionSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

class KeybordSystem: public System {
public:
    KeybordSystem(Manager* manager);
    void update() override;
    void draw() override {};
};

class AnimationSystem: public System {
public:
    AnimationSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

#endif