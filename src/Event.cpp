#include "../include/Event.h"
#include "../include/Player.h"
#include "../include/Item.h"
#include "../include/Entity.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Конструктор по умолчанию
Event::Event() : healthEffect(0), isCompleted(false) {}

/**
 * @brief Генерация случайного события
 * @param level уровень подземелья (влияет на сложность)
 */
void Event::generateRandomEvent(int level) {
    Random& rng = Random::getInstance();

    // 30% шанс на встречу с монстром
    if (rng.getBool(0.3)) {
        generateMonsterEvent(level);
    } else {
        generateRandomText(level);
    }

    // Случайное влияние на здоровье (отрицательное или положительное)
    healthEffect = rng.getInt(-15 - level * 2, 10 + level);

    // 30% шанс получить предмет (только для не-монстров)
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
            itemReward = optItem.value();
        }
    }
}

/**
 * @brief Генерация события с монстром
 */
void Event::generateMonsterEvent(int level) {
    Random& rng = Random::getInstance();

    // Создаем монстра
    monster = std::make_unique<Monster>(Monster::createRandomMonster(level));

    std::vector<std::string> monsterEventTemplates;

    // Шаблоны событий в зависимости от уровня
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

    description = monsterEventTemplates[rng.getInt(0, monsterEventTemplates.size() - 1)];

    // Добавляем информацию о монстре
    description += "\n\n" + monster->getName() + " имеет " +
                   std::to_string(monster->getHealth()) + " здоровья.\n";
    description += "Ваш урон: " + std::to_string(monster->getAttack()) + " | Ваша защита: " +
                   std::to_string(monster->getDefense());

    // Только два варианта действий для монстров
    outcomes = {"Вступить в бой", "Попытаться избежать битвы"};
}

/**
 * @brief Генерация случайного текста для события
 */
void Event::generateRandomText(int level) {
    Random& rng = Random::getInstance();

    // Шаблоны событий в зависимости от уровня
    std::vector<std::string> eventTemplates;
    std::vector<std::vector<std::string>> outcomeTemplates;

    if (level <= 2) {
        // События для начальных уровней
        eventTemplates = {
            "Вы находите старый сундук в углу комнаты.",
            "На полу лежит блестящий предмет.",
            "Вы слышите странный шорох за спиной.",
            "Из стены торчит странный рычаг.",
            "Вы замечаете чей-то скелет, прислоненный к стене."
        };

        outcomeTemplates = {
            {"Открыть сундук", "Пройти мимо"},
            {"Поднять предмет", "Не трогать"},
            {"Обернуться", "Ускорить шаг"},
            {"Дернуть рычаг", "Не трогать"},
            {"Обыскать скелет", "Пройти мимо"}
        };
    } else if (level <= 4) {
        // События для средних уровней
        eventTemplates = {
            "Вы натыкаетесь на забытый алтарь древнего божества.",
            "Из стены сочится странная светящаяся жидкость.",
            "На полу вы замечаете круг телепортации.",
            "Статуя с драгоценными камнями вместо глаз смотрит на вас.",
            "Вы слышите шепот, зовущий вас по имени."
        };

        outcomeTemplates = {
            {"Помолиться алтарю", "Пройти мимо"},
            {"Попробовать жидкость", "Обойти"},
            {"Активировать круг", "Не рисковать"},
            {"Вынуть камни", "Не трогать"},
            {"Ответить шепоту", "Игнорировать"}
        };
    } else {
        // События для глубоких уровней
        eventTemplates = {
            "Перед вами появляется призрачная фигура и обращается к вам.",
            "Вы находите древний свиток с могущественным заклинанием.",
            "Земля разверзается, открывая вход в подземную пещеру.",
            "Магический кристалл пульсирует энергией в центре комнаты.",
            "Вы чувствуете присутствие древнего стража."
        };

        outcomeTemplates = {
            {"Поговорить с духом", "Убежать"},
            {"Прочитать свиток", "Взять с собой"},
            {"Спуститься вниз", "Закрыть проход"},
            {"Коснуться кристалла", "Изучить"},
            {"Попытаться договориться", "Спрятаться"}
        };
    }

    // Выбираем случайное событие и соответствующие исходы
    size_t eventIndex = rng.getInt(0, eventTemplates.size() - 1);
    description = eventTemplates[eventIndex];

    // Добавляем контекст уровня
    description += " (Уровень подземелья: " + std::to_string(level) + ")";

    // Выбираем исходы для этого события
    if (eventIndex < outcomeTemplates.size()) {
        outcomes = outcomeTemplates[eventIndex];
    } else {
        // Запасные варианты
        outcomes = {"Выбрать вариант 1", "Выбрать вариант 2"};
    }
}

/**
 * @brief Обработка боя с монстром
 */
std::string Event::handleBattle(Player& player) {
    if (!monster) {
        return "Ошибка: монстр не найден!";
    }

    std::string result;

    result += "\n═══════════════════════════════════════════════════════════\n";
    result += "                      БОЙ С МОНСТРОМ!\n";
    result += "═══════════════════════════════════════════════════════════\n\n";
    result += "Ваш противник: " + monster->getName() + "\n";
    result += "Здоровье противника: " + std::to_string(monster->getHealth()) + "\n";
    result += "Ваш урон: " + std::to_string(player.getDamage()) + "\n\n";

    // Сравниваем урон игрока со здоровьем монстра
    if (player.getDamage() >= monster->getHealth()) {
        // Игрок побеждает
        result += "Вы мощно атакуете и побеждаете " + monster->getName() + "а одним ударом! ️\n";
        result += "Вы выходите победителем из схватки!\n";
        // Монстр побежден, ничего не выпадает
    } else {
        // Игрок проигрывает
        int damageTaken = monster->getAttack();
        player.setHealth(player.getHealth() - damageTaken);

        result += monster->getName() + " оказался слишком сильным!\n";
        result += "Он наносит вам " + std::to_string(damageTaken) + " урона!\n";

        if (player.getHealth() <= 0) {
            result += "\nВы погибли в бою...\n";
            player.setHealth(0);
        } else {
            result += "У вас осталось " + std::to_string(player.getHealth()) + " здоровья.\n";
            result += "Вы едва смогли убежать, оставляя монстра позади.\n";
        }
    }

    result += "\n═══════════════════════════════════════════════════════════\n";

    return result;
}

/**
 * @brief Попытка избежать битвы
 */
std::string Event::avoidBattle(Player& player) {
    if (!monster) {
        return "Ошибка: монстр не найден!";
    }

    Random& rng = Random::getInstance();
    std::string result;

    result += "\n═══════════════════════════════════════════════════════════\n";
    result += "                 ПОПЫТКА ИЗБЕЖАТЬ БИТВЫ\n";
    result += "═══════════════════════════════════════════════════════════\n\n";

    // 50% шанс успешно избежать битвы
    if (rng.getBool(0.5)) {
        result += "Вам удалось незаметно проскочить мимо " + monster->getName() + "а!\n";
        result += "Монстр вас не заметил.\n";
    } else {
        result += "Монстр заметил вас и атаковал!\n";

        // Монстр наносит урон, но меньше обычного
        int damageTaken = monster->getAttack() / 2;
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

/**
 * @brief Применение последствий к игроку
 */
void Event::applyEffects(Player& player, int choiceHealth, const std::string& choiceItem) {
    // Применяем влияние на здоровье
    if (choiceHealth != 0) {
        int newHealth = player.getHealth() + choiceHealth;
        player.setHealth(newHealth);

        if (choiceHealth > 0) {
            std::cout << "Вы восстановили " << choiceHealth << " здоровья!\n";
        } else if (choiceHealth < 0) {
            std::cout << "Вы потеряли " << -choiceHealth << " здоровья!\n";
        }
    }

    // Добавляем предмет, если есть
    if (!choiceItem.empty()) {
        std::unique_ptr<Item> newItem;

        // Создаем соответствующий предмет
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

/**
 * @brief Выбор варианта действия
 * @param choice номер выбранного варианта (0, 1)
 * @param player ссылка на игрока
 * @return текст результата выбора
 */
std::string Event::makeChoice(int choice, Player& player) {
    if (choice < 0 || choice >= static_cast<int>(outcomes.size())) {
        return "Неверный выбор!";
    }

    if (isCompleted) {
        return "Это событие уже завершено.";
    }

    // Если это событие с монстром
    if (monster) {
        std::string result;

        if (choice == 0) { // Вступить в бой
            result = handleBattle(player);
        } else { // Избежать битвы
            result = avoidBattle(player);
        }

        isCompleted = true;
        return result;
    }

    // Обычное событие (без монстра)
    Random& rng = Random::getInstance();
    std::string result;
    int choiceHealth = 0;
    std::string choiceItem;

    // Генерируем результат в зависимости от выбора
    switch (choice) {
        case 0: // Первый вариант
            result = "Вы решили " + outcomes[0] + ". ";
            if (rng.getBool(0.6)) {
                // Хороший исход
                choiceHealth = rng.getInt(5, 15);
                if (rng.getBool(0.3) && itemReward.empty()) {
                    choiceItem = "Малое зелье здоровья";
                }
                result += "Вам повезло! ";
            } else {
                // Плохой исход
                choiceHealth = -rng.getInt(3, 10);
                result += "Что-то пошло не так... ";
            }
            break;

        case 1: // Второй вариант
            result = "Вы решили " + outcomes[1] + ". ";
            if (rng.getBool(0.5)) {
                choiceHealth = rng.getInt(-5, 10);
                if (rng.getBool(0.2) && !itemReward.empty()) {
                    choiceItem = itemReward;
                }
                result += "Ничего особенного. ";
            } else {
                result += "Ничего не произошло. ";
            }
            break;
            
        default:
            result = "Вы просто стоите в нерешительности. ";
            break;
    }

    // Применяем эффекты
    applyEffects(player, choiceHealth, choiceItem);

    // Отмечаем событие как завершенное
    isCompleted = true;

    // Добавляем информацию о полученном уроне/лечении к результату
    if (choiceHealth > 0) {
        result += "Вы восстановили " + std::to_string(choiceHealth) + " HP.";
    } else if (choiceHealth < 0) {
        result += "Вы потеряли " + std::to_string(-choiceHealth) + " HP.";
    }

    if (!choiceItem.empty()) {
        result += " Вы получили " + choiceItem + "!";
    }

    return result;
}