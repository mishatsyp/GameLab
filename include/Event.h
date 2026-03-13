// Event.h
#ifndef EVENT_H
#define EVENT_H

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Entity.h"
#include "Player.h"
#include <memory>
#include <map>
#include "Random.h"

class Event {
private:
    std::string description;
    std::vector<std::string> outcomes;
    int healthEffect;
    std::vector<std::map<std::string, int>> rewards;
    std::string ItemReward;
    bool isCompleted;
    std::unique_ptr<Monster> monster;
    std::vector<std::string> goodMessages;
    std::vector<std::string> badMessages;
    std::vector<int> goodHeal;
    std::vector<int> badDamage;
    std::vector<int> itemChance;
    std::vector<std::string> itemType;
public:
    Event();
    void generateRandomEvent(int level, Player& p);
    std::string makeChoice(int choice, Player& player);
    std::string getDescription() const { return description; }
    const std::vector<std::string>& getOutcomes() const { return outcomes; }
    bool getIsCompleted() const { return isCompleted; }
    std::string handleBattle(Player& player);
    std::string avoidBattle(Player& player);
    bool hasMonster() const;
    Monster* getMonster() const;

private:
    void generateRandomText(int level);
    void applyEffects(Player& player, int choiceHealth, const std::string& choiceItem);
    void generateMonsterEvent(int level, Player& p);
};

#endif // EVENT_H