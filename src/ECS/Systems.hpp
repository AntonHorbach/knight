#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "ECS.hpp"
#include "Components.hpp"

class MovementSystem: public System {
public:
    MovementSystem(Manager* manager);
    void update() override;
};

#endif