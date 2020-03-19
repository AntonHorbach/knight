cmake_minimum_required(VERSION 3.0.0)
project(knight VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

add_executable(knight src/main.cpp src/game.cpp src/AssetsManager.cpp
                src/math/vec2.cpp src/ECS/MovementSystem.cpp
                src/ECS/Components.cpp src/ECS/DrawSystem.cpp
                src/ECS/JumpSystem.cpp src/ECS/CollisionSystem.cpp
                src/Events/EventBuffer.cpp src/ECS/KeybordSystem.cpp
                src/ECS/AnimationSystem.cpp src/ECS/HealthSystem.cpp)

target_link_libraries(knight SDL2 SDL2_image)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)