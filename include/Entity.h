#ifndef ENTITY_H
#define ENTITY_H

#pragma once
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
    // Сеттеры
    void setHealth(int hp) { health = hp; }
};

#endif // ENTITY_H


#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include "Random.h"

/**
 * @brief Класс монстра, наследник Entity
 * Демонстрирует конкретную реализацию абстрактного класса
 */
class Monster : public Entity {
public:
    enum class MonsterType {
        GOBLIN,
        SKELETON,
        ORC,
        DRAGON,
        GHOST
    };

private:
    MonsterType type;
    int attack;
    int defense;

    // Вспомогательный метод для получения имени
    std::string getMonsterTypeName(MonsterType type) const;

public:
    // Конструктор может генерировать монстра случайно
    explicit Monster(MonsterType monstertype, int atk, int def);
    // Реализация виртуальных методов
    virtual void takeDamage(int amount) override;
    virtual void monsterAttack(Entity& target);
    virtual int getAttackPower() const  { return attack; }
    virtual int getDefense() const { return defense; }
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
    static Monster createRandomMonster(int level);
};

#endif // MONSTER_H
