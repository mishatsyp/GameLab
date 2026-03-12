# Dungeon Crawler

## Project review
A console RPG game in the Dungeon Crawler genre,
where the player explores dungeons, fights monsters and
moves to new levels. The project was developed in C++23 with
using modern language features and an object-oriented approach.

## Developers
- Michael - classes Player, GameEngine
- Suzanne - classes Room, Dungeon
- Lubov' - classes Event, Random, Entity
- Leonid - classes Item, Screen

## Technologies
- **Language**: C++23
- **Build**: CMake 4.00+
- **Test**: Google Test
- **Version control**: Git (GitHub)

## Architecture
The project is based on the following key classes:
- **GameEngine** - central gameplay management class
- **Dungeon** - dungeon generation and management (room matrix)
- **Room** - room with events or exit
- **Player** - Player status, inventory, health
- **Event** is an abstract base class for all events
- **Entity** - enemies/npc class
- **Random** - random choice system
- **Screen** - interface rendering
- **Item** - usage and properties of items