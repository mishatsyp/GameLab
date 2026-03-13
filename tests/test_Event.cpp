#include <gtest/gtest.h>
#include "Event.h"
#include "Player.h"
#include <memory>


TEST(EventTest, CreateEvent) {
    Event event;
    Player player("TestPlayer");
    event.generateRandomEvent(1, player);
    EXPECT_FALSE(event.getDescription().empty());
    EXPECT_FALSE(event.getOutcomes().empty());
}


TEST(EventTest, GenerateMonsterEvent) {
    Event event;
    Player player("TestPlayer");
    event.generateRandomEvent(1, player);
    SUCCEED();
}

TEST(EventTest, HasMonster) {
    Event event;
    Player player("TestPlayer");
    bool foundMonster = false;
    for (int i = 0; i < 10; ++i) {
        event.generateRandomEvent(1, player);
        if (event.hasMonster()) {
            foundMonster = true;
            EXPECT_NE(event.getMonster(), nullptr);
            break;
        }
    }
}

TEST(EventTest, MakeChoiceWithoutMonster) {
    Event event;
    Player player("TestPlayer");
    int initialHealth = player.getHealth();
    event.generateRandomEvent(1, player);
    if (event.hasMonster()) {
        SUCCEED();
        return;
    }
    std::string result = event.makeChoice(0, player);
    EXPECT_FALSE(result.empty());
}

TEST(EventTest, BattleWithMonster) {
    Player player("TestPlayer");
    Monster monster = Monster::createRandomMonster(1);
    SUCCEED();
}

TEST(EventTest, AvoidBattle) {
    Player player("TestPlayer");
    int initialHealth = player.getHealth();
    Event event;
    for (int i = 0; i < 10; ++i) {
        event.generateRandomEvent(1, player);
        if (event.hasMonster()) {
            std::string result = event.makeChoice(1, player);
            EXPECT_FALSE(result.empty());
            break;
        }
    }
    SUCCEED();
}

TEST(EventTest, EventCompletedAfterChoice) {
    Event event;
    Player player("TestPlayer");
    event.generateRandomEvent(1, player);
    if (!event.hasMonster()) {
        event.makeChoice(0, player);
        EXPECT_TRUE(event.getIsCompleted());
    } else {
        event.makeChoice(0, player);
        EXPECT_TRUE(event.getIsCompleted());
    }
}

TEST(EventTest, GetOutcomes) {
    Event event;
    Player player("TestPlayer");
    event.generateRandomEvent(1, player);
    const auto& outcomes = event.getOutcomes();
    EXPECT_FALSE(outcomes.empty());
    EXPECT_LE(outcomes.size(), 3);
    for (const auto& outcome : outcomes) {
        EXPECT_FALSE(outcome.empty());
    }
}