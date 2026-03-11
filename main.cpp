#include <iostream>
#include "include/GameEngine.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 > nul");  // принудительно UTF-8
#endif
    GameEngine game_engine;
    game_engine.initialize();
}