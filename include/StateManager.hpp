// StateManager.hpp
#pragma once
#include <memory>
#include <stack>
#include "GameState.hpp"

class StateManager {
public:
    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    GameState* getCurrentState();

private:
    std::stack<std::unique_ptr<GameState>> states;
};

