// GameEngine.h
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <memory>
#include <optional>
#include <chrono>
#include <vector>
#include <functional>
#include "Player.h"
#include "Dungeon.h"

/**
 * @brief Центральный класс движка игры
 */
class GameEngine {
private:
    std::unique_ptr<Player> player;
    std::unique_ptr<Dungeon> currentDungeon;
    bool isRunning;
    int currentLevel;

    // Для замера времени (требование из ТЗ)
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    TimePoint gameStartTime;

public:
    GameEngine();
    ~GameEngine() = default;

    // Запрещаем копирование
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;

    // Разрешаем перемещение
    GameEngine(GameEngine&&) noexcept = default;
    GameEngine& operator=(GameEngine&&) noexcept = default;

    /**
     * @brief Вызов меню игры
     */
    void menu();

    /**
     * @brief Инициализация новой игры
     */
    bool initialize();

    // /**
    //  * @brief Обработка ввода игрока
    //  * @return std::optional<char> - введенная команда
    //  */
    // std::optional<char> processInput();

    /**
     * @brief Обработка текущей комнаты
     */
    void handleCurrentRoom();

    /**
     * @brief Обработка боя
     */
    void handleBattle();

    /**
     * @brief Переход на следующий уровень подземелья
     */
    void nextLevel();

    // /**
    //  * @brief Отрисовка текущего состояния
    //  */
    // void render() const;
    //
    // Исключение для движка

    class GameException : public std::runtime_error {
    public:
        explicit GameException(const std::string& message)
            : std::runtime_error("Game Error: " + message) {}
    };
};

#endif // GAME_ENGINE_H