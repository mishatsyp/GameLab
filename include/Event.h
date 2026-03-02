// Event.h
#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <memory>
#include "Player.h"
#include "Random.h"

/**
 * @brief Класс события - просто текстовое событие с последствиями
 */
class Event {
private:
    std::string description;      // Описание того, что случилось
    std::vector<std::string> outcomes; // Варианты действий (2-3 варианта)
    int healthEffect;             // Влияние на здоровье (может быть отрицательным)
    std::string itemReward;       // Предмет, который можно получить (если есть)
    bool isCompleted;             // Завершено ли событие
public:
    Event();
    /**
     * @brief Генерация случайного события
     * @param level уровень подземелья (влияет на сложность)
     */
    void generateRandomEvent(int level);
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

private:
    /**
     * @brief Генерация случайного текста для события
     */
    void generateRandomText(int level);

    /**
     * @brief Применение последствий к игроку
     */
    void applyEffects(Player& player, int choiceHealth,x const std::string& choiceItem);
};

#endif // EVENT_H