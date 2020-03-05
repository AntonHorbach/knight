#include <SDL2/SDL.h>

#include <deque>
#include <algorithm>

class EventBuffer {
public:
    bool pollEvent(SDL_Event* event);
    void update();

private:
    std::deque<SDL_Event> events;
};