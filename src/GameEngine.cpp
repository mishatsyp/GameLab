#include "../include/Dungeon.h"
#include "../include/Player.h"

GameEngine::GameEngine()
    : isRunning(false)
    , currentLevel(1)
    , gameStartTime(Clock::now()) {
    // Инициализация полей
}

void GameEngine::menu() {
    Screen screen;
    screen.drawMenu();
}

bool GameEngine::initialize() {
    try {
        std::cout << "Инициализация игры..." << std::endl;

        // Создаем игрока
        std::string playerName;
        std::cout << "Введите имя игрока: ";
        std::getline(std::cin, playerName);

        if (playerName.empty()) {
            playerName = "Hero";
        }

        player = std::make_unique<Player>(playerName);

        // Создаем первый уровень подземелья
        currentDungeon = std::make_unique<Dungeon>(currentLevel);

        isRunning = true;

        // Вызываем меню из Screen
        menu();

        //screen.drawDungeonMap(dungeon, player)

        while (player->getHealth() > 0) {
            int choice;
            Screen::chooseAction();
            std::cin >> choice;
            switch (choice) {
                case 1:
                    //look

                case 2:
                    player->showInventory();

                case 3:
                    //move to the next room

                default:
                    std::cout << "Choose another option";
            }
        }

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка инициализации: " << e.what() << std::endl;
        return false;
    }
}

void GameEngine::handleCurrentRoom() {
    Screen::drawCurrentRoomInfo(currentDungeon);
}

void GameEngine::handleBattle() {
    Screen screen;
    // screen.drawBattle(player, ...); нужен monster
}

void GameEngine::nextLevel() {
    Screen screen;
    if (!currentDungeon) {
        throw GameException("Данж не инициализирован");
    }

    currentLevel++;
    Screen::drawMessage("ПЕРЕХОД НА УРОВЕНЬ ");

    // Создаем новый уровень подземелья
    currentDungeon = std::make_unique<Dungeon>(currentLevel);
}