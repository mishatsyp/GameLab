// Room.cpp
#include "../include/Room.h"
#include "../include/Random.h"
#include "../include/Screen.h"
#include "../include/Event.h"
#include <iostream>

Room::Room(RoomType roomType, Player& p) : type(roomType), isExplored(false) {
    generateRoomContent(p);
}

void Room::generateRoomContent(Player& p) {
    Random& rng = Random::getInstance();
    // Если тип не задан (EMPTY), рандомно выбираем между EMPTY и EVENT
    if (type == RoomType::EMPTY) {
        // 70% шанс на ивент, 30% на пустую
        int chance = rng.getInt(1, 100);
        if (chance <= 70) {
            type = RoomType::EVENT;
        }
    }

    // Если комната с ивентом - создаем событие
    if (type == RoomType::EVENT) {
        roomEvent = std::make_unique<Event>();
        roomEvent->generateRandomEvent(1, p); // уровень 1 по умолчанию
    }
}

void Room::look(Player& player) {
    switch(type) {
        case RoomType::EMPTY:
            if (isExplored) {
                Screen::drawMessage("Вы снова в пустой комнате. Ничего не изменилось.");
            } else {
                Screen::drawMessage("Пустая комната. Здесь ничего нет.");
                isExplored = true;
            }
            break;

        case RoomType::EVENT:
            if (roomEvent) {
                // Если событие уже завершено
                if (roomEvent->getIsCompleted()) {
                    if (isExplored) {
                        Screen::drawMessage("Вы уже прошли это событие. В комнате ничего не изменилось.");
                    } else {
                        Screen::drawMessage("Вы прошли событие. Комната выглядит обычно.");
                        isExplored = true;
                    }
                    break;  // важно выйти!
                }

                // Если событие активно
                if (isExplored) {
                    Screen::drawMessage("Вы возвращаетесь к событию...");
                }

                while (!roomEvent->getIsCompleted()) {
                    if (!isExplored) {
                        Screen::drawMessage(roomEvent->getDescription());
                    }

                    std::string outcomesText = "Выберите действие:\n";
                    for (size_t i = 0; i < roomEvent->getOutcomes().size(); i++) {
                        outcomesText += std::to_string(i+1) + ". " + roomEvent->getOutcomes()[i] + "\n";
                    }
                    Screen::drawMessage(outcomesText);

                    int choice = -1;
                    bool validInput = false;

                    while (!validInput) {
                        std::cout << "Ваш выбор: ";
                        std::cin >> choice;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            Screen::drawMessage("Ошибка ввода! Введите число.");
                            continue;
                        }

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (choice >= 1 && choice <= static_cast<int>(roomEvent->getOutcomes().size())) {
                            validInput = true;
                        } else {
                            Screen::drawMessage("Неверный выбор! Введите число от 1 до " +
                                               std::to_string(roomEvent->getOutcomes().size()));
                        }
                    }

                    std::string result = roomEvent->makeChoice(choice - 1, player);
                    Screen::drawMessage(result);
                }

                // Событие завершено
                isExplored = true;
                Screen::drawMessage("Вы прошли событие. Теперь комната пуста.");

            } else {
                Screen::drawMessage("Странная комната...");
            }
            break;

        case RoomType::EXIT:
            Screen::drawMessage("Вы нашли выход на следующий уровень!");
            break;
    }
}