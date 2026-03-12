#include <gtest/gtest.h>
#include "../include/Screen.h"
#include "../include/Player.h"
#include "../include/Dungeon.h"


TEST(ScreenTest, ClearScreen) {
    EXPECT_NO_THROW(Screen::clearScreen());
}

TEST(ScreenTest, DrawMessage) {
    EXPECT_NO_THROW(Screen::drawMessage("Тестовое сообщение"));
}


TEST(ScreenTest, DrawMenu) {
    EXPECT_NO_THROW(Screen::drawMenu());
}

TEST(ScreenTest, ChooseAction) {
    EXPECT_NO_THROW(Screen::chooseAction());
}


TEST(ScreenTest, DrawGameOver) {
    EXPECT_NO_THROW(Screen::drawGameOver());
}


TEST(ScreenTest, DrawInventory) {
    Player player("Hero");
    EXPECT_NO_THROW(Screen::drawInventory(player));
}

TEST(ScreenTest, DrawDungeonMap) {
    Player player("Hero");
    Dungeon dungeon(player);
    EXPECT_NO_THROW(Screen::drawDungeonMap(dungeon));
}