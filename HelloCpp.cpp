#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Character
{
    std::string name;
    int level = 0;
    int health = 0;
    int maxHealth = 0;
    int mana = 0;
    int gold = 0;
};

enum class Action {
    Attack = 1,
    CastSpell = 2,
    Heal = 3,
    Exit = 4
};

enum class BattleResult
{
    Victory,
    Defeat,
    Escaped
};

void ShowBattleMenu() {
    std::cout << "\n=== Battle Menu ===\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Cast spell\n";
    std::cout << "3. Heal\n";
    std::cout << "4. Exit\n";
}

void ShowStatus(const Character& character)
{
    if (character.health <= 0)
    {
        std::cout << "\n" << character.name << " Status: Dead\n";
    }
    else if (character.health <= 25)
    {
        std::cout << "\n" << character.name << " Status: Critical\n";
    }
    else
    {
        std::cout << "\n" << character.name << " Status: Alive\n";
    }
}

void ApplyDamage(Character& character, int damage)
{
    if (damage <= 0)
    {
        return;
    }

    character.health -= damage;

    if (character.health < 0)
    {
        character.health = 0;
    }
}

bool CanCastSpell(int mana, int spellCost)
{
    return mana >= spellCost;
}

bool SpendMana(Character& character, int manaCost)
{
    if (manaCost <= 0 || character.mana < manaCost)
    {
        return false;
    }

    character.mana -= manaCost;
    return true;
}

bool Heal(Character& character, int healAmount)
{
    if (healAmount <= 0)
    {
        std::cout << "Heal amount must be greater than 0.\n";
        return false;
    }

    if (character.health <= 0)
    {
        std::cout << character.name
            << " is dead and cannot be healed.\n";
        return false;
    }

    if (character.health >= character.maxHealth)
    {
        std::cout << character.name
            << " is already at full health.\n";
        return false;
    }

    character.health += healAmount;

    if (character.health > character.maxHealth)
    {
        character.health = character.maxHealth;
    }

    return true;
}

void ShowProfile(const Character& character)
{
    std::cout << "\n=== Character Profile ===\n";
    std::cout << "Name: " << character.name << "\n";
    std::cout << "Level: " << character.level << "\n";
    std::cout << "Health: "
        << character.health
        << "/"
        << character.maxHealth
        << "\n";
    std::cout << "Mana: " << character.mana << "\n";
    std::cout << "Gold: " << character.gold << "\n";
}

int ReadInt(const std::string& prompt, int minValue)
{
    int value = 0;

    while (true)
    {
        std::cout << prompt;

        if (std::cin >> value && value >= minValue)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return value;
        }

        if (std::cin.fail())
        {
            std::cout << "Enter a valid number.\n";
            std::cin.clear();
        }
        else
        {
            std::cout << "Value must be at least "
                << minValue
                << ".\n";
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

int ReadIntRange(
    const std::string& prompt,
    int minValue,
    int maxValue
)
{
    while (true)
    {
        int value = ReadInt(prompt, minValue);

        if (value <= maxValue)
        {
            return value;
        }

        std::cout << "Value must be between "
            << minValue
            << " and "
            << maxValue
            << ".\n";
    }
}

Action ReadAction() 
{
    ShowBattleMenu();

    int choice = ReadIntRange("Choose action: ", 1, 4);

    Action action = static_cast<Action>(choice);

    return action;
}

Character CreatePlayer()
{
    Character newPlayer{};

    std::cout << "\nEnter player name: ";
    std::cin >> newPlayer.name;

    newPlayer.level = ReadInt("Enter player level: ", 1);
    newPlayer.maxHealth = ReadInt(
        "Enter player max health: ",
        1
    );
    newPlayer.health = newPlayer.maxHealth;
    newPlayer.mana = ReadInt("Enter player mana: ", 0);
    newPlayer.gold = ReadInt("Enter player gold: ", 0);

    return newPlayer;
}

Character CreateEnemy()
{
    Character newEnemy{};

    std::cout << "\nEnter new enemy name: ";
    std::cin >> newEnemy.name;

    newEnemy.level = ReadInt("Enter new enemy level: ", 1);
    newEnemy.maxHealth = ReadInt(
        "Enter new enemy max health: ",
        1
    );
    newEnemy.health = newEnemy.maxHealth;
    newEnemy.mana = ReadInt("Enter new enemy mana: ", 0);
    newEnemy.gold = ReadInt("Enter new enemy gold: ", 0);

    return newEnemy;
}

void ShowEnemies(const std::vector<Character>& enemies)
{
    std::cout << "\n=== Enemy List ===\n";

    for (const Character& enemy : enemies)
    {
        std::cout << enemy.name
            << " - Health: "
            << enemy.health
            << "/"
            << enemy.maxHealth
            << ", Gold: "
            << enemy.gold
            << "\n";
    }
}

void ShowParty(const std::vector<Character>& party)
{
    std::cout << "\n=== Party ===\n";

    for (const Character& partyMember : party)
    {
        ShowProfile(partyMember);
    }
}

std::size_t ChooseEnemy(const std::vector<Character>& enemies)
{
    int maxChoice = static_cast<int>(enemies.size());

    int enemyChoice = ReadIntRange(
        "Choose your enemy 1-"
        + std::to_string(maxChoice)
        + ": ",
        1,
        maxChoice
    );

    return static_cast<std::size_t>(enemyChoice - 1);
}

BattleResult Fight(Character& player, Character& enemy)
{
    int round = 1;
    const int enemyDamage = 10;
    const int spellCost = 20;
    const int spellDamage = 25;
    const int healAmount = 30;

    while (enemy.health > 0 && player.health > 0)
    {
        std::cout << "\n=== Round " << round << " ===\n";

        Action action = ReadAction();

        bool actionSucceeded = false;

        switch (action)
        {
        case Action::Attack:
        {
            int damage = ReadInt(
                "Enter damage to " + enemy.name + ": ",
                1
            );

            ApplyDamage(enemy, damage);
            actionSucceeded = true;

            ShowStatus(enemy);

            std::cout << enemy.name
                << " health: "
                << enemy.health
                << "\n";
            break;
        }

        case Action::CastSpell:
        {
            if (!SpendMana(player, spellCost)) 
            {
                std::cout << "Not enough mana.\n";
                break;
            }

            ApplyDamage(enemy, spellDamage);
            std::cout << player.name
                << " casts a spell for "
                << spellDamage
                << " damage.\n";

            ShowStatus(enemy);
            
            std::cout << enemy.name
                << " health: "
                << enemy.health
                << "\n";

            std::cout << player.name
                << " mana: "
                << player.mana
                << "\n";

            actionSucceeded = true;
            break;
        }

        case Action::Heal:
        {
            if (!Heal(player, healAmount))
            {
                break;
            }
            actionSucceeded = true;
            std::cout << player.name << " heals\n";
            std::cout << player.name << " health: " << player.health << "/" << player.maxHealth<<"\n";
            
            break;
        }

        case Action::Exit:
            std::cout << "Player left the battle.\n";
            return BattleResult::Escaped;
        }

        if (!actionSucceeded)
        {
            continue;
        }

        if (enemy.health > 0)
        {
            std::cout << enemy.name
                << " attacks for "
                << enemyDamage
                << " damage.\n";

            ApplyDamage(player, enemyDamage);
            ShowStatus(player);
        }

        std::cout << player.name
            << " health: "
            << player.health
            << "\n";

        round++;
    }

    if (player.health > 0) {
        return BattleResult::Victory;
    }

    return BattleResult::Defeat;
}

bool DamageCharacterByName(
    std::vector<Character>& party,
    const std::string& targetName,
    int damage
)
{
    if (damage <= 0)
    {
        return false;
    }

    for (Character& character : party)
    {
        if (character.name == targetName)
        {
            ApplyDamage(character, damage);
            return true;
        }
    }

    return false;
}

bool HealCharacterByName(
    std::vector<Character>& party,
    const std::string& targetName,
    int healAmount
)
{
    if (healAmount <= 0)
    {
        return false;
    }

    for (Character& character : party)
    {
        if (character.name == targetName)
        {
            return Heal(character, healAmount);
        }
    }

    return false;
}

int main()
{
    std::cout << "=== Welcome to the Battle Game ===\n";
    std::cout << std::boolalpha;

    Character player = CreatePlayer();

    std::vector<Character> party{
        player,
        {"DPS", 10, 100, 100, 50, 200},
        {"TANK", 10, 200, 200, 30, 100},
        {"HEALER", 10, 60, 60, 100, 150}
    };

    std::vector<Character> enemies{
        {"Goblin", 3, 60, 60, 0, 25},
        {"Orc", 5, 100, 100, 0, 40},
        {"Mage", 7, 80, 80, 100, 70}
    };

    ShowParty(party);

    bool damageResult = DamageCharacterByName(
        party,
        "TANK",
        70
    );

    bool healResult = HealCharacterByName(
        party,
        "TANK",
        100
    );

    std::cout << "\nDamage result: "
        << damageResult
        << "\n";

    std::cout << "Heal result: "
        << healResult
        << "\n";

    ShowParty(party);

    enemies.push_back(CreateEnemy());
    ShowEnemies(enemies);

    std::size_t enemyIndex = ChooseEnemy(enemies);
    Character& enemy = enemies[enemyIndex];

    const int spellCost = 20;

    ShowProfile(player);
    ShowProfile(enemy);

    if (CanCastSpell(player.mana, spellCost))
    {
        std::cout << "\nMagic: Spell ready\n";
    }
    else
    {
        std::cout << "\nMagic: Not enough mana!\n";
    }

    std::cout << "\nBattle starts in:\n";

    for (int i = 3; i >= 1; i--)
    {
        std::cout << i << "\n";
    }

    std::cout << "Fight!\n";

    BattleResult battleResult = Fight(player, enemy);

    switch (battleResult)
    {
    case BattleResult::Victory:
        std::cout << "\n" << player.name << " WINS!\n";

        player.gold += enemy.gold;

        std::cout << "\nReward: "
            << enemy.gold
            << " gold!\n";

        enemy.gold = 0;
        ShowProfile(enemy);
        break;

    case BattleResult::Defeat:
        std::cout << "\n" << enemy.name << " WINS!\n";
        std::cout << "\nYou don't receive a reward!\n";
        ShowProfile(enemy);
        break;

    case BattleResult::Escaped:
        std::cout << "\nYou escaped from the battle.\n";
        break;
    }

    ShowProfile(player);
    ShowEnemies(enemies);

}