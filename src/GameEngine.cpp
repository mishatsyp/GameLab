#include "../include/Dungeon.h"
#include "../include/Player.h"
#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/GameEngine.h"
#include "../include/Dungeon.h"

GameEngine::~GameEngine() {}

GameEngine::GameEngine()
    : isRunning(false)
    , currentLevel(1) {}

void GameEngine::menu() {
    Screen screen;
    screen.drawMenu();
}

bool GameEngine::initialize() {
    try {
        std::cout << "Инициализация игры..." << std::endl;

        // спавним игрока
        std::string playerName;
        std::cout << "Введите имя игрока: ";
        std::getline(std::cin, playerName);

        if (playerName.empty()) {
            playerName = "Hero";
        }

        player = std::make_unique<Player>(playerName);

        // первый уровень подземелья
        currentDungeon = std::make_unique<Dungeon>(*player);

        isRunning = true;

        menu();
        int des;
        std::cin>>des;
        if (des==2){return false;}
        else {
            Screen::clearScreen();

        while (player->getHealth()>0 && player->getLevel()<=5) {
            int choice;
            Screen::chooseAction();
            std::cin >> choice;
            Screen::clearScreen();
            switch (choice) {
                case 1: {
                    int x = currentDungeon->getCurrentX();
                    int y = currentDungeon->getCurrentY();

                    Room* currentRoom = currentDungeon->getRoomAt(x, y);

                    if (currentRoom){
                        currentRoom->look(*player);  // осматриваем комнату
                        if (currentRoom->getisExplored()) {
                            player->setCheckedRooms(player->getCheckedRooms() + 1);
                        }
                    }
                    break;
                }

                case 2:
                    player->showInventory();
                    std::cout << "\nКоманды: u [номер] - использовать, d [номер] - выбросить, b - назад\n";

                    char command;
                    int itemIndex;
                    std::cin >> command;

                    if (command == 'u') {
                        std::cin >> itemIndex;
                        int inventorySize = player->getInventorySize();

                        if (itemIndex >= 1 && itemIndex <= inventorySize) {
                            auto itemOpt = player->getItem(itemIndex - 1);
                            if (itemOpt.has_value()) {
                                auto item = itemOpt.value();
                                item->use(*player);

                                // прочность айтема
                                if (item->getItemDurability() <= 0) {
                                    std::cout << "Предмет сломался и удален из инвентаря.\n";
                                    player->removeItem(itemIndex - 1);
                                }
                            } else {
                                std::cout << "Ошибка: предмет не найден!\n";
                            }
                        } else {
                            std::cout << "Неверный номер предмета! У вас " << inventorySize << " предметов.\n";
                        }
                    } else if (command == 'b' || command == 'B') {
                        std::cout << "Возврат к основным действиям.\n";
                    } else if (command == 'd' || command == 'D') {
                        std::cin >> itemIndex;
                        int inventorySize = player->getInventorySize();
                        if (itemIndex >= 1 && itemIndex <= inventorySize) {
                            auto itemOpt = player->getItem(itemIndex - 1);
                            if (itemOpt.has_value()) {
                                auto item = itemOpt.value();
                                std::cout << "Вы выбросили: " << item->getName() << "\n";
                                player->removeItem(itemIndex - 1);
                            }
                        } else {
                            std::cout << "Неверный номер предмета!\n";
                        }
                    }else {
                        std::cout << "Неверная команда!\n";
                    }
                    break;

                case 3: {
                    int currentX = currentDungeon->getCurrentX();
                    int currentY = currentDungeon->getCurrentY();

                    char direction;
                    Screen::drawDungeonMap(*currentDungeon);
                    Screen::drawMessage("Куда хотите пойти? (w - вверх, s - вниз, a - влево, d - вправо): ");
                    std::cin >> direction;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очищаем буфер

                    int newX = currentX;
                    int newY = currentY;

                    switch (direction) {
                        case 'w': newY--; break;
                        case 's': newY++; break;
                        case 'a': newX--; break;
                        case 'd': newX++; break;
                        default:
                            std::cout << "Неверное направление!\n";
                            Screen::drawMessage("Нажмите Enter...");
                            std::cin.get();
                            Screen::clearScreen();
                            break;
                    }

                    if (currentDungeon->getCell(newX, newY) == 1 || currentDungeon->getCell(newX, newY) == 2) {
                        switch (direction) {
                            case 'w': currentDungeon->moveUp();
                                std::cout << "Вы перешли в другую комнату.\n";
                                break;
                            case 's': currentDungeon->moveDown();
                                std::cout << "Вы перешли в другую комнату.\n";
                                break;
                            case 'a': currentDungeon->moveLeft();
                                std::cout << "Вы перешли в другую комнату.\n";
                                break;
                            case 'd': currentDungeon->moveRight();
                                std::cout << "Вы перешли в другую комнату.\n";
                                break;
                        }

                        if (currentDungeon->getCell(newX, newY) == 2) {
                            if (player->getCheckedRooms() >= 5) {
                                Screen::drawMessage("Вы нашли выход на следующий уровень!");
                                nextLevel();
                            } else {
                                Screen::drawMessage("Вы не обыскали нужное количество комнат!");
                            }
                        }

                        // пауза во избежания бага
                        Screen::drawMessage("Нажмите Enter чтобы продолжить...");
                        std::cin.get();
                        Screen::clearScreen();

                    } else {
                        Screen::drawMessage("Там стена! Нельзя пройти.");
                        Screen::drawMessage("Нажмите Enter...");
                        std::cin.get();
                        Screen::clearScreen();
                    }
                    break;
                }

                default:
                    std::cout << "Choose another option";
            }
        }
            Screen::drawGameOver();
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка инициализации: " << e.what() << std::endl;
        return false;
    }
}

// void GameEngine::handleCurrentRoom() {
//     Screen::drawCurrentRoomInfo(*currentDungeon);
// }

// void GameEngine::handleBattle(Player& p) {
//     .handleBattle(p);
// }

NextLevelResult GameEngine::nextLevel() {
    if (!currentDungeon) {
        return NextLevelError{"Данж не инициализирован"};
    }

    player->setLevel(player->getLevel() + 1);
    player->setCheckedRooms(0);
    currentLevel++;
    currentDungeon = std::make_unique<Dungeon>(*player);

    return NextLevelSuccess{currentLevel};
}