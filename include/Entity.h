// Entity.h
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>

/**
 * @brief Абстрактный базовый класс для всех существ
 * Демонстрирует чисто виртуальные функции и полиморфизм
 */
class Entity {
protected:
    std::string name;
    int health;
    // int maxHealth;
public:
    Entity(const std::string& entityName, int hp);
    virtual ~Entity() = default;  // Виртуальный деструктор обязательно!

    // Запрещаем копирование (можно разрешить, но осторожно)
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // Разрешаем перемещение
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) noexcept = default;

    // Чисто виртуальные методы (делают класс абстрактным)
    virtual void takeDamage(int amount) = 0;
    // virtual std::string getDescription() const = 0;
    virtual bool isAlive() const = 0;

    // Обычные виртуальные методы (можно переопределить)
    virtual void heal(int amount);
    // virtual void buff(int attackBonus, int defenseBonus);

    // Геттеры (могут быть constexpr если возвращают константы)
    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    // int getMaxHealth() const { return maxHealth; }
    // int getAttackPower() const { return attack; }
    // int getDefense() const { return defense; }

    // Сеттеры
    void setHealth(int hp) { health = hp; }
};

#endif // ENTITY_H

// Monster.h - наследник Entity
#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include "Random.h"

/**
 * @brief Класс монстра, наследник Entity
 * Демонстрирует конкретную реализацию абстрактного класса
 */
class Monster : public Entity {
private:
    enum class MonsterType {
        GOBLIN,
        SKELETON,
        ORC,
        DRAGON,
        GHOST
    };

    MonsterType type;
    int attack;
    int defense;

public:
    // Конструктор может генерировать монстра случайно
    explicit Monster(MonsterType monstertype, int atk, int def);
    // Реализация виртуальных методов
    virtual void takeDamage(int amount) override;
    virtual void attack(Entity& target) override;
    // virtual std::string getDescription() const override;
    virtual bool isAlive() const override;

    // Статические constexpr методы для характеристик монстров
    static constexpr int getBaseHealth(MonsterType t) {
        switch(t) {
            case MonsterType::GOBLIN: return 15;
            case MonsterType::SKELETON: return 25;
            case MonsterType::ORC: return 40;
            case MonsterType::DRAGON: return 100;
            case MonsterType::GHOST: return 30;
            default: return 20;
        }
    }
};

#endif // MONSTER_H
