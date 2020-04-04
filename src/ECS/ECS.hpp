#ifndef ECS_HPP
#define ECS_HPP

#include <vector>
#include <iostream>
#include <memory>
#include <array>
#include <bitset>

inline size_t getComponentTypeID() noexcept {
    static size_t typeID = 0;
    return typeID++;
}

template <typename T> [[nodiscard]]
inline size_t getComponentID() noexcept {
    static size_t componentID = getComponentTypeID();
    return componentID;
}

struct Component {};
class Manager;

constexpr size_t MAX_COMPONENTS = 24;

class Entity {
    Manager* m_manager;
    std::array<std::unique_ptr<Component>, MAX_COMPONENTS> components;
    std::bitset<MAX_COMPONENTS> componentsState;

public:
    explicit Entity(Manager* manager): m_manager(manager) {}

    template <typename T, typename... Args>
    bool addComponent(Args&&... args) {
        size_t componentID = getComponentID<T>();

        if(componentID >= MAX_COMPONENTS) {
            return false;
        }

        components[componentID] = std::unique_ptr<Component>
                                    {new T(std::forward<Args>(args)...)};
        componentsState[componentID] = true;

        return true;
    }

    template <typename T>
    bool hasComponent() {
        size_t componentID = getComponentID<T>();

        if(componentID >= MAX_COMPONENTS) {
            return false;
        }
        
        return componentsState[componentID];
    }

    template <typename T>
    void deleteComponent() {
        size_t componentID = getComponentID<T>();

        if(componentID < MAX_COMPONENTS) {
            componentsState[componentID] = false;
        }
    }

    template <typename T>
    T& getComponent() {
        return *(static_cast<T*>(components[getComponentID<T>()].get()));
    }
};

class System {
protected:
    Manager* manager;

public:
    explicit System(Manager* m): manager(m) {}

    virtual void update() = 0;
    virtual void draw() = 0;

    virtual ~System() = default;
};

using shEntity = std::shared_ptr<Entity>;
using unqSystem = std::unique_ptr<System>;

class Manager {
    std::vector<shEntity> entities;
    std::vector<unqSystem> systems; 

public:
    Manager() = default;

    shEntity createEntity() {
        shEntity entity(new Entity(this));

        entities.push_back(entity);

        return entity;
    }

    template <typename T>
    void addSystem() {
        systems.push_back(std::make_unique<T>(this));
    }

    [[nodiscard]]
    const std::vector<shEntity>& getEntities() const {
        return entities;
    }

    [[nodiscard]]
    std::vector<shEntity>& getEntities() {
        return entities;
    }

    void update() {
        for(auto& sys : systems) {
            sys->update();
        }
    }

    void draw() {
        for(auto& sys : systems) {
            sys->draw();
        }
    }
};

#endif