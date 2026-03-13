#ifndef SCREEN_H
#define SCREEN_H

#pragma once
#include <iostream>
#include <string>
#include <iostream>

class Player;
class  Dungeon;

class Screen {
public:
    static void clearScreen();
    static void drawDungeonMap(const Dungeon& dungeon);
    static void drawInventory(const Player& player);
    static void drawMessage(const std::string& message);
    static void drawMenu();
    static void chooseAction();
    static void drawGameOver();
};

#endif