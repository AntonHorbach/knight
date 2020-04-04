#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "ECS.hpp"
#include "Components.hpp"

class MovementSystem: public System {
public:
    explicit MovementSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

class DrawSystem: public System {
public:
    explicit DrawSystem(Manager* manager);
    void update() override;
    void draw() override;
};

class JumpSystem: public System {
public:
    explicit JumpSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

class CollisionSystem: public System {
public:
    explicit CollisionSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

class KeyboardSystem: public System {
public:
    explicit KeyboardSystem(Manager* manager);
    void update() override;
    void draw() override {};
};

class AnimationSystem: public System {
public:
    explicit AnimationSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

class HealthSystem: public System {
public:
    explicit HealthSystem(Manager* manager);
    void update() override;
    void draw() override;
};

class AttackSystem: public System {
public:
    explicit AttackSystem(Manager* manager);
    void update() override;
    void draw() override {}
};

#endif