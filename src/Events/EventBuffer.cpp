#include "EventBuffer.hpp"

bool EventBuffer::pollEvent(SDL_Event* event) {
    SDL_Event new_event;

    while(SDL_PollEvent(&new_event)) {
        events.push_back(new_event);
    }

    if(!events.empty()) {
        *event = events.front();
        events.pop_front();

        return true;
    }

    return false;
}

void EventBuffer::update() {
    if(events.empty()) return;

    SDL_Event last_event = events.back();

    auto compare ([&last_event](SDL_Event& event) -> bool
    {
        if(event.type == SDL_KEYDOWN
            && event.key.keysym.sym == last_event.key.keysym.sym)
        {
            return true;
        }
        else return false;
    });

    if(last_event.type == SDL_KEYUP) {    
        events.erase(std::remove_if(events.begin(), events.end(), compare),
            events.end());
    }
}