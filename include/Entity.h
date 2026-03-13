#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include <string>
#include <memory>

class Entity {
protected:
    std::string name;
    int health;
    // int maxHealth;
public:
    Entity(const std::string& entityName, int hp);
    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) noexcept = default;

    virtual void takeDamage(int amount) = 0;
    virtual bool isAlive() const = 0;

    virtual void heal(int amount);

    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    void setHealth(int hp) { health = hp; }
};

#endif // ENTITY_H


#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include "Random.h"

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

    std::string getMonsterTypeName(MonsterType type) const;

public:
    explicit Monster(MonsterType monstertype, int atk, int def);
    virtual void takeDamage(int amount) override;
    virtual void monsterAttack(Entity& target);
    virtual int getAttackPower() const  { return attack; }
    virtual int getDefense() const { return defense; }
    virtual bool isAlive() const override;

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
