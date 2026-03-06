#include "..//include/Entity.h"
#include "..//include/Random.h"
#include <string>
#include <algorithm>


Entity::Entity(const std::string& entityName, int hp)
    : name(entityName), health(hp) {}

void Entity::heal(int amount) {
    if (amount > 0) {
        health += amount;
    }
}

Monster::Monster(MonsterType monsterType, int atk, int def)
    : Entity(getMonsterTypeName(monsterType), getBaseHealth(monsterType))
    , type(monsterType)
    , attack(atk)
    , defense(def) {}

void Monster::takeDamage(int amount) {
    if (amount > 0) {
        int reducedDamage = std::max(1, amount - defense);
        health -= reducedDamage;
        if (health < 0) health = 0;
    }
}

void Monster::monsterAttack(Entity& target) {
    Random& rng = Random::getInstance();
    int damageVariation = rng.getInt(80, 120);
    int finalDamage = (attack * damageVariation) / 100;

    target.takeDamage(finalDamage);
}

bool Monster::isAlive() const {
    return health > 0;
}

std::string Monster::getMonsterTypeName(MonsterType type) const {
    switch(type) {
        case MonsterType::GOBLIN:   return "Гоблин";
        case MonsterType::SKELETON: return "Скелет";
        case MonsterType::ORC:       return "Орк";
        case MonsterType::DRAGON:    return "Дракон";
        case MonsterType::GHOST:     return "Призрак";
        default:                     return "Неизвестное существо";
    }
}

Monster Monster::createRandomMonster(int level) {
    Random& rng = Random::getInstance();

    MonsterType type;
    if (level <= 2) {
        type = static_cast<MonsterType>(rng.getInt(0, 1));
    } else if (level <= 4) {
        type = static_cast<MonsterType>(rng.getInt(1, 3));
    } else {
        type = static_cast<MonsterType>(rng.getInt(2, 4));
    }

    int baseAttack = 0;
    int baseDefense = 0;

    switch(type) {
        case MonsterType::GOBLIN:
            baseAttack = 5;
            baseDefense = 2;
            break;
        case MonsterType::SKELETON:
            baseAttack = 8;
            baseDefense = 4;
            break;
        case MonsterType::ORC:
            baseAttack = 12;
            baseDefense = 6;
            break;
        case MonsterType::DRAGON:
            baseAttack = 20;
            baseDefense = 15;
            break;
        case MonsterType::GHOST:
            baseAttack = 10;
            baseDefense = 8;
            break;
    }

    int attack = baseAttack + (level - 1) * 2;
    int defense = baseDefense + (level - 1);

    return Monster(type, attack, defense);
}