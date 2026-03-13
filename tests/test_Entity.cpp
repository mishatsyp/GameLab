#include <gtest/gtest.h>
#include "Entity.h"
#include "Random.h"


TEST(EntityTest, CreateEntity) {
    Monster monster(Monster::MonsterType::GOBLIN, 5, 2);
    EXPECT_EQ(monster.getName(), "Гоблин");
    EXPECT_EQ(monster.getHealth(), Monster::getBaseHealth(Monster::MonsterType::GOBLIN));
    EXPECT_EQ(monster.getAttackPower(), 5);
    EXPECT_EQ(monster.getDefense(), 2);
}

TEST(EntityTest, GetBaseHealth) {
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::GOBLIN), 15);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::SKELETON), 25);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::ORC), 40);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::DRAGON), 100);
    EXPECT_EQ(Monster::getBaseHealth(Monster::MonsterType::GHOST), 30);
}

TEST(EntityTest, TakeDamageWithDefense) {
    Monster monster(Monster::MonsterType::GOBLIN, 5, 3);
    int initialHealth = monster.getHealth();
    monster.takeDamage(10);
    EXPECT_LT(monster.getHealth(), initialHealth);
    EXPECT_GT(monster.getHealth(), initialHealth - 10);
}

TEST(EntityTest, IsAlive) {
    Monster monster(Monster::MonsterType::GOBLIN, 5, 2);
    EXPECT_TRUE(monster.isAlive());
    monster.takeDamage(100);
    EXPECT_FALSE(monster.isAlive());
}

TEST(EntityTest, CreateRandomMonsterByLevel) {
    Monster monster1 = Monster::createRandomMonster(1);
    EXPECT_GT(monster1.getHealth(), 0);
    EXPECT_GT(monster1.getAttackPower(), 0);
    Monster monster5 = Monster::createRandomMonster(5);
    EXPECT_GT(monster5.getHealth(), monster1.getHealth());
}

TEST(EntityTest, HealEntity) {
    Monster monster(Monster::MonsterType::GOBLIN, 5, 2);
    int initialHealth = monster.getHealth();
    monster.takeDamage(10);
    int damagedHealth = monster.getHealth();
    EXPECT_LT(damagedHealth, initialHealth);
    monster.heal(5);
    EXPECT_GT(monster.getHealth(), damagedHealth);
}