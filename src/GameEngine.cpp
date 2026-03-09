#include "../include/Dungeon.h"
#include "../include/Player.h"

GameEngine::GameEngine()
    : isRunning(false)
    , currentLevel(1)
    , gameStartTime(Clock::now()) {
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
        currentDungeon = std::make_unique<Dungeon>();

        isRunning = true;

        // Вызываем меню из Screen
        menu();

        Screen::drawDungeonMap(currentDungeon); // может в цикл?

        while (player->getHealth() > 0 || player->getLevel()<=5) {
            int choice;
            Screen::chooseAction();
            std::cin >> choice;
            Screen::clearScreen();
            switch (choice) {
                case 1:
                    //look
                    break;

                case 2:
                    player->showInventory();
                    std::cout << "\nИспользовать: u [номер]  |  Назад: b\n";

                    char command;
                    int itemIndex;
                    std::cin >> command;

                    if (command == 'u') {
                        std::cin >> itemIndex;
                        // Индексация предметов с 1 для удобства пользователя
                        int inventorySize = player->getInventorySize();

                        if (itemIndex >= 1 && itemIndex <= inventorySize) {
                            // Получаем предмет по индексу (конвертируем в 0-базовый индекс)
                            Item* item = player->getItem(itemIndex - 1);

                            if (item) {
                                // Пытаемся использовать предмет
                                try {
                                    // Используем существующий метод useItem, но он пока не реализован
                                    // Временно используем прямой вызов use()
                                    item->use(*player);
                                    std::cout << "Предмет \"" << item->getName() << "\" использован.\n";

                                    // Проверяем, не сломался ли предмет (для оружия и брони)
                                    if (item->getItemDurability() <= 0) {
                                        std::cout << "Предмет сломался и удален из инвентаря.\n";
                                        player->removeItem(itemIndex - 1);
                                    }
                                } catch (const std::exception& e) {
                                    std::cout << "Ошибка при использовании предмета: " << e.what() << "\n";
                                }
                            } else {
                                std::cout << "Ошибка: предмет не найден!\n";
                            }
                        } else {
                            std::cout << "Неверный номер предмета! У вас " << inventorySize << " предметов.\n";
                        }
                    } else if (command == 'b' || command == 'B') {
                        // Просто выходим из инвентаря
                        std::cout << "Возврат к основным действиям.\n";
                    } else {
                        std::cout << "Неверная команда!\n";
                    }
                    break;

                case 3: {
                    // Получаем текущие координаты игрока в данже
                    int currentX = currentDungeon->getCurrentX();
                    int currentY = currentDungeon->getCurrentY();

                    // Спрашиваем у игрока направление движения
                    char direction;
                    Screen::drawDungeonMap();
                    Screen::drawMessage("Куда хотите пойти? (w - вверх, s - вниз, a - влево, d - вправо): ");
                    std::cin >> direction;

                    // Определяем новые координаты в зависимости от направления
                    int newX = currentX;
                    int newY = currentY;

                    switch (direction) {
                        case 'w':
                            newY--;
                            break;
                        case 's':
                            newY++;
                            break;
                        case 'a':
                            newX--;
                            break;
                        case 'd':
                            newX++;
                            break;
                        default:
                            std::cout << "Неверное направление!\n";
                            break;
                    }

                    if (currentDungeon->getCell(newX, newY) == 1 || currentDungeon->getCell(newX, newY) == 2) {
                        // Можно двигаться - обновляем позицию игрока
                        switch (direction) {
                            case 'w':
                                currentDungeon->moveUp();
                                break;
                            case 's':
                                currentDungeon->moveDown();
                                break;
                            case 'a':
                                currentDungeon->moveLeft();
                                break;
                            case 'd':
                                currentDungeon->moveRight();
                                break;
                            default:
                                Screen::drawMessage("Choose direction pls");
                        }
                        std::cout << "Вы перешли в другую комнату.\n";

                        // Если это выход (значение 2) - переходим на следующий уровень
                        if (currentDungeon->getCell(newX, newY) == 2) {
                            Screen::drawMessage("Вы нашли выход на следующий уровень!");
                            nextLevel();
                        }
                    } else {
                        Screen::drawMessage("Там стена! Нельзя пройти.");
                    }
                    break;
                }

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
    player->setLevel(player->getLevel()+1);
    if (!currentDungeon) {
        throw GameException("Данж не инициализирован");
    }

    currentLevel++;
    Screen::drawMessage("ПЕРЕХОД НА УРОВЕНЬ ");

    // Создаем новый уровень подземелья
    currentDungeon = std::make_unique<Dungeon>(); // обработка нового уровня (а может ну его?)
}