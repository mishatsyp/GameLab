#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#pragma once
#include <memory>
#include <chrono>
#include <variant>
#include <string>



class Player;
class Dungeon;

struct NextLevelSuccess {
    int newLevel;
};

struct NextLevelError {
    std::string reason;
};

using NextLevelResult = std::variant<NextLevelSuccess, NextLevelError>;

class GameEngine {
private:
    std::unique_ptr<Player> player;
    std::unique_ptr<Dungeon> currentDungeon;
    bool isRunning;
    int currentLevel;
    
public:
    GameEngine();
    ~GameEngine();

    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;
    GameEngine(GameEngine&&) noexcept = default;
    GameEngine& operator=(GameEngine&&) noexcept = default;

    void menu();
    bool initialize();
    NextLevelResult nextLevel();

    class GameException : public std::runtime_error {
    public:
        explicit GameException(const std::string& message)
            : std::runtime_error("Game Error: " + message) {}
    };
};

#endif // GAME_ENGINE_H