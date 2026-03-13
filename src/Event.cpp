#include "../include/Event.h"
#include "../include/Player.h"
#include "../include/Item.h"
#include "../include/Entity.h"
#include "../include/Screen.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

Event::Event() : healthEffect(0), isCompleted(false) {}

void Event::generateRandomEvent(int level, Player& p) {
    Random& rng = Random::getInstance();

    if (rng.getBool(0.3)) {
        generateMonsterEvent(level, p);
    } else {
        generateRandomText(level);
    }

    healthEffect = rng.getInt(-15 - level * 2, 10 + level);

    if (!monster && rng.getBool(0.3)) {
        std::vector<std::string> possibleItems = {
            "Зелье здоровья",
            "Меч",
            "Кинжал",
            "Щит",
            "Амулет"
        };
        auto optItem = rng.getRandomElement(possibleItems);
        if (optItem.has_value()) {
            ItemReward = optItem.value();
        }
    }
}

void Event::generateMonsterEvent(int level, Player& p) {
    Random& rng = Random::getInstance();

    monster = std::make_unique<Monster>(Monster::createRandomMonster(level));

    std::vector<std::string> monsterEventTemplates;

    if (level <= 2) {
        monsterEventTemplates = {
            "На вас набрасывается " + monster->getName() + "!",
            "Из темноты выпрыгивает " + monster->getName() + "!",
            "Вы слышите рычание. Это " + monster->getName() + "!",
            "Маленький " + monster->getName() + " преграждает путь!"
        };
    } else if (level <= 4) {
        monsterEventTemplates = {
            "Огромный " + monster->getName() + " преграждает вам путь!",
            "Вы потревожили логово " + monster->getName() + "а!",
            "Из тени появляется " + monster->getName() + "!",
            "Злобный " + monster->getName() + " атакует!"
        };
    } else {
        monsterEventTemplates = {
            "Древний " + monster->getName() + " пробуждается от сна!",
            "Перед вами предстает ужасающий " + monster->getName() + "!",
            "Стены содрогаются от рева " + monster->getName() + "а!",
            "Легендарный " + monster->getName() + " охраняет проход!"
        };
    }

    description = monsterEventTemplates[rng.getInt(0, static_cast<int>(monsterEventTemplates.size()) - 1)];

    description += "\n\n" + monster->getName() + " имеет " +
                   std::to_string(monster->getHealth()) + " здоровья.\n";
    description += "Ваш урон: " + std::to_string(p.getTotalDamage());
    outcomes = {"Вступить в бой", "Попытаться избежать битвы"};
}

void Event::generateRandomText(int level) {
    Random& rng = Random::getInstance();

    struct EventTemplate {
        std::string description;
        std::vector<std::string> outcomes;
        std::vector<std::string> goodMessages;
        std::vector<std::string> badMessages;
        std::vector<int> goodHeal;
        std::vector<int> badDamage;
        std::vector<int> itemChance;
        std::vector<std::string> itemType;
    };

    std::vector<EventTemplate> templates = {
        {
            "Вы находите старый деревянный сундук в углу комнаты.",
            {"Аккуратно открыть", "Пнуть ногой", "Пройти мимо"},
            {
                "Вы осторожно открываете крышку. Внутри что-то блестит!",
                "Сундук открывается от удара, содержимое разлетается по полу",
                "Вы проходите мимо, оставляя сундук нетронутым"
            },
            {
                "Из сундука вылетает пружинный механизм и ранит вас!",
                "Сундук взрывается от магической ловушки!",
                ""
            },
            {15, 5, 0},
            {10, 15, 0},
            {70, 40, 0},
            {"Any", "Potion", ""}
        },

        {
            "В центре комнаты стоит древний алтарь с тускло мерцающим камнем.",
            {"Помолиться", "Забрать камень", "Осмотреть символы"},
            {
                "Божество благословляет вас! Тепло разливается по телу.",
                "Камень пульсирует в руках, даруя силу.",
                "Вы замечаете скрытый механизм в алтаре и находите тайник."
            },
            {
                "Божество гневается и насылает проклятие!",
                "Камень взрывается магической энергией!",
                "Вы активируете ловушку, и стены начинают сдвигаться!"
            },
            {20, 10, 15},
            {15, 20, 10},
            {50, 60, 80},
            {"Potion", "Armor", "Weapon"}
        },

        {
            "У стены прислонен скелет в истлевших доспехах. Рядом лежит меч.",
            {"Взять меч", "Обыскать скелет", "Похоронить останки"},
            {
                "Меч все еще острый! Отличная находка.",
                "В кармане вы находите несколько монет и амулет.",
                "Скелет благодарно рассыпается в прах."
            },
            {
                "Меч рассыпается в руках, оставляя ржавую пыль.",
                "Скелет оживает и атакует!",
                "Вы тратите время на пустое благородство."
            },
            {0, 5, 10},
            {0, 12, 0},
            {80, 50, 30},
            {"Weapon", "Armor", "Potion"}
        },

        {
            "В центре комнаты бьет небольшой фонтан с голубоватой светящейся водой.",
            {"Напиться", "Набрать воды", "Бросить монетку"},
            {
                "Вода освежает и наполняет силой!",
                "Вы набираете воду в бутылку. Она мягко светится.",
                "Монетка исчезает в воде, и фонтан начинает светиться ярче."
            },
            {
                "Вода оказывается кислотой!",
                "Вода испаряется при прикосновении.",
                "Монетка застревает и фонтан перестает работать."
            },
            {25, 10, 5},
            {15, 0, 5},
            {0, 70, 40},
            {"", "Potion", "Armor"}
        },

        {
            "Комната опутана паутиной. В темноте виднеются несколько крупных пауков.",
            {"Сжечь паутину", "Пробраться тихо", "Бежать"},
            {
                "Паутина вспыхивает, освещая комнату. Пауки разбегаются!",
                "Вы тихо проскальзываете мимо спящих пауков.",
                "Вы успеваете выбежать до того, как пауки вас заметили."
            },
            {
                "Паутина загорается слишком сильно, огонь перекидывается на вас!",
                "Пауки просыпаются и нападают!",
                "Пауки бегут за вами и кусают!"
            },
            {10, 5, 0},
            {15, 18, 12},
            {30, 20, 0},
            {"Potion", "Weapon", ""}
        },

        {
            "Дорогу преграждает глубокий разлом. Когда-то здесь был мост.",
            {"Попытаться перепрыгнуть", "Найти обходной путь", "Вернуться назад"},
            {
                "Вы успешно перепрыгиваете разлом!",
                "Вы находите узкую тропу вдоль стены.",
                "Вы возвращаетесь, но замечаете блестящий предмет на полу."
            },
            {
                "Вы срываетесь вниз, но успеваете ухватиться за край!",
                "Тропа обрывается, вы падаете!",
                ""
            },
            {0, 10, 5},
            {20, 15, 0},
            {0, 40, 60},
            {"", "Potion", "Armor"}
        },

        {
            "На полу растут странные светящиеся грибы. Воздух наполнен спорами.",
            {"Съесть гриб", "Собрать грибы", "Обойти стороной"},
            {
                "Гриб оказывается съедобным и вкусным!",
                "Вы аккуратно собираете грибы в мешок.",
                "Вы обходите поляну, но находите странный камень."
            },
            {
                "Гриб ядовит! Вы чувствуете головокружение.",
                "Споры попадают в дыхательные пути, вызывая кашель.",
                "Вы наступаете на скользкий гриб и падаете."
            },
            {15, 5, 0},
            {12, 8, 5},
            {0, 70, 30},
            {"", "Potion", "Armor"}
        },

        {
            "В углу стоит человек в плаще. Он предлагает купить у него зелье.",
            {"Купить зелье", "Украсть", "Игнорировать"},
            {
                "Торговец дает вам зелье. Оно выглядит качественным!",
                "Вам удается незаметно стащить зелье!",
                "Вы проходите мимо."
            },
            {
                "Торговец обманул вас! Зелье испорчено.",
                "Торговец замечает кражу и бьет вас посохом!",
                ""
            },
            {5, 0, 0},
            {10, 12, 0},
            {100, 80, 0},
            {"Potion", "Potion", ""}
        },

        {
            "В центре комнаты стоит каменная статуя с драгоценными камнями вместо глаз.",
            {"Вынуть камни", "Поклониться статуе", "Осмотреть постамент"},
            {
                "Камни легко вынимаются! Они очень красивые.",
                "Статуя оживает на мгновение и благословляет вас.",
                "В постаменте вы находите тайник с оружием!"
            },
            {
                "Статуя оживает и атакует вас!",
                "Статуя игнорирует вас, но пол проваливается!",
                "Вы активируете ловушку!"
            },
            {0, 15, 10},
            {20, 15, 12},
            {90, 50, 80},
            {"Armor", "Potion", "Weapon"}
        },

        {
            "Вы попадаете в комнату, заставленную древними книжными шкафами.",
            {"Почитать книги", "Поискать тайник", "Забрать свитки"},
            {
                "Вы находите книгу с заклинаниями!",
                "За шкафом спрятан сундук с сокровищами!",
                "Свитки содержат древние знания."
            },
            {
                "Книга оказывается проклятой!",
                "Шкаф падает на вас!",
                "Свитки рассыпаются в пыль."
            },
            {10, 5, 5},
            {15, 12, 8},
            {60, 80, 70},
            {"Weapon", "Armor", "Potion"}
        }
    };

    size_t index = rng.getInt(0, templates.size() - 1);
    description = templates[index].description;
    outcomes = templates[index].outcomes;
    goodMessages = templates[index].goodMessages;
    badMessages = templates[index].badMessages;
    goodHeal = templates[index].goodHeal;
    badDamage = templates[index].badDamage;
    itemChance = templates[index].itemChance;
    itemType = templates[index].itemType;
}

std::string Event::handleBattle(Player& player) {
    if (!monster) {
        return "Ошибка: монстр не найден!";
    }

    std::string result;
    Random& rng = Random::getInstance();

    result += "\n═══════════════════════════════════════════════════════════\n";
    result += "                      БОЙ С МОНСТРОМ!\n";
    result += "═══════════════════════════════════════════════════════════\n\n";

    bool playerTurn = true;
    bool battleActive = true;

    while (battleActive) {
        result += "\n──────────────────────────────────────────────────\n";
        result += "Ваше здоровье: " + std::to_string(player.getHealth()) + "\n";
        result += "Здоровье " + monster->getName() + ": " + std::to_string(monster->getHealth()) + "\n";

        if (playerTurn) {
            result += "\nВаш ход. Выберите действие:\n";
            result += "1. Атаковать\n";
            result += "2. Защищаться (уменьшает урон, но тратит прочность оружия)\n";

            int choice;
            std::cout << result;
            result.clear();
            std::cout << "Ваш выбор: ";
            std::cin >> choice;

            if (choice == 1) {
                if (rng.getBool(0.8)) {
                    int damage = player.getDamage();
                    monster->setHealth(monster->getHealth() - damage);
                    result += "Вы наносите " + std::to_string(damage) + " урона!\n";
                    if (player.getEquippedWeapon()) {
                        player.getEquippedWeapon()->reduceDurability(2);
                        if (player.getEquippedWeapon()->isBroken()) {
                            result += "⚔️ Ваше оружие сломалось!\n";
                        }
                    }
                } else {
                    result += "Вы промахнулись!\n";
                }
            }
            else if (choice == 2) {
                result += "Вы встаете в защитную стойку!\n";
                player.setDefending(true);

                if (player.getEquippedWeapon()) {
                    player.getEquippedWeapon()->reduceDurability(1);
                    if (player.getEquippedWeapon()->isBroken()) {
                        result += "⚔️ Ваше оружие сломалось!\n";
                    }
                }
            }
            if (monster->getHealth() <= 0) {
                result += "\n═══════════════════════════════════════════════════════════\n";
                result += "🏆 ВЫ ПОБЕДИЛИ! 🏆\n";
                result += monster->getName() + " повержен!\n";

                if (rng.getBool(0.3)) {
                    result += "Из монстра выпал трофей: ";
                    int itemType = rng.getInt(0, 2);
                    if (itemType == 0) {
                        player.addItem(std::make_unique<Potion>("Зелье здоровья", 20, 1));
                        result += "Зелье здоровья!";
                    } else if (itemType == 1) {
                        player.addItem(std::make_unique<Weapon>("Коготь монстра", 8, 50));
                        result += "Коготь монстра!";
                    } else {
                        player.addItem(std::make_unique<Armor>("Шкура монстра", 4, 50));
                        result += "Шкура монстра!";
                    }
                    result += "\n";
                }

                battleActive = false;
                break;
            }

            playerTurn = false;
        }
        else {
            result += "\nХод " + monster->getName() + "!\n";

            if (rng.getBool(0.7)) {
                int damage = monster->getAttackPower();

                if (player.GetisDefending()) {
                    damage /= 2;
                    if (damage < 1) damage = 1;
                    result += monster->getName() + " атакует, но ваша защита ослабляет удар!\n";
                }

                player.setHealth(player.getHealth() - damage);
                result += monster->getName() + " наносит " + std::to_string(damage) + " урона!\n";

                if (player.getEquippedArmor()) {
                    player.getEquippedArmor()->reduceDurability(1);
                    if (player.getEquippedArmor()->isBroken()) {
                        result += "🛡️ Ваша броня разрушилась!\n";
                    }
                }
            } else {
                result += monster->getName() + " промахнулся!\n";
            }


            player.setDefending(false);

            if (player.getHealth() <= 0) {
                result += "\n═══════════════════════════════════════════════════════════\n";
                result += "💀 ВЫ ПОГИБЛИ... 💀\n";
                result += "Монстр оказался сильнее.\n";
                player.setHealth(0);
                battleActive = false;
                break;
            }

            playerTurn = true;
        }
        result += "──────────────────────────────────────────────────\n";
    }

    result += "\n═══════════════════════════════════════════════════════════\n";
    return result;
}
std::string Event::avoidBattle(Player& player) {
    if (!monster) {
        return "Ошибка: монстр не найден!";
    }
    Random& rng = Random::getInstance();
    std::string result;

    result += "\n═══════════════════════════════════════════════════════════\n";
    result += "                 ПОПЫТКА ИЗБЕЖАТЬ БИТВЫ\n";
    result += "═══════════════════════════════════════════════════════════\n\n";
    if (rng.getBool(0.5)) {
        result += "Вам удалось незаметно проскочить мимо " + monster->getName() + "а!\n";
        result += "Монстр вас не заметил.\n";
    } else {
        result += "Монстр заметил вас и атаковал!\n";
        int damageTaken = player.getDamage() / 2;
        if (damageTaken < 1) damageTaken = 1;

        player.setHealth(player.getHealth() - damageTaken);

        result += monster->getName() + " успел задеть вас, нанеся " +
                  std::to_string(damageTaken) + " урона!\n";

        if (player.getHealth() <= 0) {
            result += "\nВы погибли при попытке убежать...\n";
            player.setHealth(0);
        } else {
            result += "У вас осталось " + std::to_string(player.getHealth()) + " здоровья.\n";
            result += "Вам удалось вырваться и убежать.\n";
        }
    }
    result += "\n═══════════════════════════════════════════════════════════\n";
    return result;
}
void Event::applyEffects(Player& player, int choiceHealth, const std::string& choiceItem) {
    if (choiceHealth != 0) {
        int newHealth = player.getHealth() + choiceHealth;
        player.setHealth(newHealth);
        if (choiceHealth > 0) {
            std::cout << "Вы восстановили " << choiceHealth << " здоровья!\n";
        } else if (choiceHealth < 0) {
            std::cout << "Вы потеряли " << -choiceHealth << " здоровья!\n";
        }
    }
    if (!choiceItem.empty()) {
        std::unique_ptr<Item> newItem;
        if (choiceItem.find("Зелье") != std::string::npos) {
            newItem = std::make_unique<Potion>(choiceItem, 20, 3);
        } else if (choiceItem.find("Меч") != std::string::npos) {
            newItem = std::make_unique<Weapon>(choiceItem, 15);
        } else if (choiceItem.find("Кинжал") != std::string::npos) {
            newItem = std::make_unique<Weapon>(choiceItem, 8);
        } else if (choiceItem.find("Щит") != std::string::npos) {
            newItem = std::make_unique<Armor>(choiceItem, 5, 100);
        } else if (choiceItem.find("Амулет") != std::string::npos) {
            newItem = std::make_unique<Armor>(choiceItem, 3, 50);
        } else {
            newItem = std::make_unique<Potion>(choiceItem, 15, 2);
        }
        if (player.addItem(std::move(newItem))) {
            std::cout << "Вы получили предмет: " << choiceItem << "!\n";
        } else {
            std::cout << "Инвентарь полон! Предмет " << choiceItem << " не может быть добавлен.\n";
        }
    }
}
std::string Event::makeChoice(int choice, Player& player) {
    if (choice < 0 || choice >= static_cast<int>(outcomes.size())) {
        return "Неверный выбор!";
    }

    if (isCompleted) {
        return "Это событие уже завершено.";
    }

    player.setCheckedRooms(player.getCheckedRooms() + 1);

    if (monster) {
        std::string result;
        if (choice == 0) {
            result = handleBattle(player);
        } else {
            result = avoidBattle(player);
        }
        isCompleted = true;
        return result;
    }

    Random& rng = Random::getInstance();
    bool isGood = rng.getBool(0.6);

    std::string result;

    if (isGood) {
        result = goodMessages[choice];
        player.setHealth(player.getHealth() + goodHeal[choice]);

        if (rng.getInt(1, 100) <= itemChance[choice]) {
            std::shared_ptr<Item> newItem;

            if (itemType[choice] == "Weapon") {
                int dmg = rng.getInt(5, 15);
                newItem = std::make_shared<Weapon>("Оружие", dmg, 100);
            }
            else if (itemType[choice] == "Armor") {
                int def = rng.getInt(3, 10);
                newItem = std::make_shared<Armor>("Броня", def, 100);
            }
            else if (itemType[choice] == "Potion") {
                int heal = rng.getInt(15, 30);
                newItem = std::make_shared<Potion>("Зелье", heal, 1);
            }
            else if (itemType[choice] == "Any") {
                int type = rng.getInt(0, 2);
                if (type == 0) {
                    int dmg = rng.getInt(5, 15);
                    int dur = rng.getInt(30, 100);
                    if (dur <= 0) dur = 50;
                    newItem = std::make_shared<Weapon>("Оружие", dmg, dur);
                } else if (type == 1) {
                    int def = rng.getInt(3, 10);
                    int dur = rng.getInt(30, 100);
                    if (dur <= 0) dur = 50;
                    newItem = std::make_shared<Armor>("Броня", def, dur);
                } else {
                    int heal = rng.getInt(15, 30);
                    newItem = std::make_shared<Potion>("Зелье", heal, 1);
                }
            }

            if (newItem) {
                if (player.addItem(newItem)) {
                    result += " Вы получили " + newItem->getName() + "!";
                } else {
                    result += " Инвентарь полон! Предмет не поместился.";
                }
            }
        }
    } else {
        result = badMessages[choice];
        player.setHealth(player.getHealth() - badDamage[choice]);
        result += " Вы потеряли " + std::to_string(badDamage[choice]) + " HP.";
    }

    isCompleted = true;
    return result;
}
bool Event::hasMonster() const {
    return monster ? true : false;
}

Monster* Event::getMonster() const {
    return monster ? monster.get() : nullptr;
}