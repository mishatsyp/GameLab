// Event.h
#ifndef EVENT_H
#define EVENT_H

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Entity.h"
#include "Player.h"
#include <memory>
#include <map>
#include "Random.h"

/**
 * @brief Класс события - просто текстовое событие с последствиями
 */
class Event {
private:
    std::string description;      // Описание того, что случилось
    std::vector<std::string> outcomes; // Варианты действий (2-3 варианта)
    int healthEffect;             // Влияние на здоровье (может быть отрицательным)
    std::vector<std::map<std::string, int>> rewards;
    std::string ItemReward;
    bool isCompleted;             // Завершено ли событие
    std::unique_ptr<Monster> monster;
public:
    Event();
    /**
     * @brief Генерация случайного события
     * @param level уровень подземелья (влияет на сложность)
     */
    void generateRandomEvent(int level, Player& p);
    /**
     * @brief Запуск события
     * @param player ссылка на игрока
     */
    // void trigger(Player& player);
    // /**
    //  * @brief Выбор варианта действия
    //  * @param choice номер выбранного варианта (0, 1 или 2)
    //  * @param player ссылка на игрока
    //  * @return текст результата выбора
    //  */
    std::string makeChoice(int choice, Player& player);
    // Геттеры
    std::string getDescription() const { return description; }
    const std::vector<std::string>& getOutcomes() const { return outcomes; }
    bool getIsCompleted() const { return isCompleted; }
    std::string handleBattle(Player& player);
    std::string avoidBattle(Player& player);
    bool hasMonster() const;
    Monster* getMonster() const;

private:
    /**
     * @brief Генерация случайного текста для события
     */
    void generateRandomText(int level);

    /**
     * @brief Применение последствий к игроку
     */
    void applyEffects(Player& player, int choiceHealth, const std::string& choiceItem);
    void generateMonsterEvent(int level, Player& p);
};

#endif // EVENT_H