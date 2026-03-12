#include <gtest/gtest.h>
#include "Entity.h"
#include "Random.h"

// Тест 1: Проверка создания Entity
TEST(EntityTest, CreateEntity) {
    // Entity абстрактный, тестируем через Monster
    Monster monster(Monster::MonsterType::GOBLIN, 5, 2);

    EXPECT_EQ(monster.getName(), "Гоблин");
    EXPECT_EQ(monster.getHealth(), Monster::getBaseHealth(Monster::MonsterType::GOBLIN));
    EXPECT_EQ(monster.getAttackPower(), 5);
    EXPECT_EQ(monster.getDefense(), 2);
}

// Тест 2: Проверка получения базового здоровья для разных типов
TEST(EntityTest, GetBaseHealth) {
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::GOBLIN), 15);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::SKELETON), 25);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::ORC), 40);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::DRAGON), 100);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::GHOST), 30);
}

// Тест 3: Проверка takeDamage с учетом защиты
TEST(EntityTest, TakeDamageWithDefense) {
    Monster monster(Monster::MonsterType::GOBLIN, 5, 3);
    int initialHealth = monster.getHealth();

    monster.takeDamage(10); // Урон должен уменьшиться на defense

    EXPECT_LT(monster.getHealth(), initialHealth);
    EXPECT_GT(monster.getHealth(), initialHealth - 10); // Из-за защиты урон должен быть меньше 10
}

// Тест 4: Проверка isAlive
TEST(EntityTest, IsAlive) {
    Monster monster(Monster::MonsterType::GOBLIN, 5, 2);

    EXPECT_TRUE(monster.isAlive());

    monster.takeDamage(100); // Смертельный урон
    EXPECT_FALSE(monster.isAlive());
}

// Тест 5: Проверка создания случайного монстра по уровню
TEST(EntityTest, CreateRandomMonsterByLevel) {
    // Монстр 1-го уровня
    Monster monster1 = Monster::createRandomMonster(1);
    EXPECT_GT(monster1.getHealth(), 0);
    EXPECT_GT(monster1.getAttackPower(), 0);

    // Монстр 5-го уровня (должен быть сильнее)
    Monster monster5 = Monster::createRandomMonster(5);
    EXPECT_GT(monster5.getHealth(), monster1.getHealth());
}

// Тест 6: Проверка heal
TEST(EntityTest, HealEntity) {
    Monster monster(Monster::MonsterType::GOBLIN, 5, 2);
    int initialHealth = monster.getHealth();

    monster.takeDamage(10);
    int damagedHealth = monster.getHealth();
    EXPECT_LT(damagedHealth, initialHealth);

    monster.heal(5);
    EXPECT_GT(monster.getHealth(), damagedHealth);
}