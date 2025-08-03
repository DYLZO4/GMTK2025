#include "StateManager.hpp"

void StateManager::pushState(std::unique_ptr<GameState> state) {
    if (!states.empty())
        states.top()->onExit();
    states.push(std::move(state));
    states.top()->onEnter();
}

void StateManager::popState() {
    if (!states.empty()) {
        states.top()->onExit();
        states.pop();
    }
    if (!states.empty())
        states.top()->onEnter();
}

void StateManager::changeState(std::unique_ptr<GameState> state) {
    popState();
    pushState(std::move(state));
}

GameState* StateManager::getCurrentState() {
    return states.empty() ? nullptr : states.top().get();
}

