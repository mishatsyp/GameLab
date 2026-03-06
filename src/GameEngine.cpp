#include "../include/Dungeon.h"

GameEngine::GameEngine()
    : isRunning(false)
    , currentLevel(1)
    , gameStartTime(Clock::now()) {
    // Инициализация полей
}

void GameEngine::menu() {
    Screen screen;
    //screen.drawMenu(); нечего вставить
}

bool GameEngine::initialize() {
    // try {
    //     std::cout << "Инициализация игры..." << std::endl;
    //
    //     // Создаем игрока
    //     std::string playerName;
    //     std::cout << "Введите имя игрока: ";
    //     std::getline(std::cin, playerName);
    //
    //     if (playerName.empty()) {
    //         playerName = "Hero";
    //     }
    //
    //     player = std::make_unique<Player>(playerName);
    //
    //     // Создаем первый уровень подземелья
    //     currentDungeon = std::make_unique<Dungeon>(currentLevel);
    //
    //     isRunning = true;
    //     std::cout << "Игра успешно инициализирована!" << std::endl;
    //
    //     // Вызываем меню из Screen
    //     menu();
    //
    //     return true;
    // } catch (const std::exception& e) {
    //     std::cerr << "Ошибка инициализации: " << e.what() << std::endl;
    //     return false;
    // }
    return true;
}

void GameEngine::handleCurrentRoom() {
    Screen screen;
    screen.drawCurrentRoomInfo(currentDungeon);
}

void GameEngine::handleBattle() {
    Screen screen;
    // screen.drawBattle(player, ...); нужен monster
}

void GameEngine::nextLevel() {
    if (!currentDungeon) {
        throw GameException("Данж не инициализирован");
    }

    currentLevel++;
    // std::cout << "\n=== ПЕРЕХОД НА УРОВЕНЬ " << currentLevel << " ===" << std::endl; сообщение через screen

    // Создаем новый уровень подземелья
    currentDungeon = std::make_unique<Dungeon>(currentLevel);
}