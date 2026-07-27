#include <iostream>
#include <string>
#include <vector>

struct Character
{
    std::string name;
    int level = 0;
    int health = 0;
    int mana = 0;
    int gold = 0;
};

void ShowStatus(const Character& character)
{
    if (character.health <= 0)
    {
        std::cout <<character.name << " Status: Dead\n";
    }
    else if (character.health <= 25)
    {
        std::cout << character.name << " Status: Critical\n";
    }
    else
    {
        std::cout << character.name << " Status: Alive\n";
    }
}

void ApplyDamage(Character& character, int damage)
{
    character.health = character.health - damage;
    
    if (character.health < 0)
    {
        character.health = 0;
    }
}

bool CanCastSpell(int mana, int spellCost)
{
    return mana >= spellCost;
}

void ShowProfile(const Character& character)
{
    std::cout << "\n=== Character Profile ===\n";
    std::cout << "Name: " << character.name << "\n";
    std::cout << "Level: " << character.level << "\n";
    std::cout << "Health: " << character.health << "\n";
    std::cout << "Mana: " << character.mana << "\n";
    std::cout << "Gold: " << character.gold << "\n";
}

Character CreateEnemy() 
{
    Character newEnemy{};

    std::cout << "Enter New Enemy name: ";
    std::cin >> newEnemy.name;

    std::cout << "New Enemy level: ";
    std::cin >> newEnemy.level;

    while (newEnemy.level <= 0) {
        std::cout << "level must be greater than 0\n" << "Enter new enemy level: ";
        std::cin >> newEnemy.level;
    }

    std::cout << "New Enemy health: ";
    std::cin >> newEnemy.health;

    while (newEnemy.health <= 0) {
        std::cout << "health must be greater than 0\n" << "Enter new enemy health: ";
        std::cin >> newEnemy.health;
    }

    std::cout << "New Enemy mana: ";
    std::cin >> newEnemy.mana;
    while (newEnemy.mana < 0) {
        std::cout << "mana cannot be negative\n" << "Enter new enemy mana: ";
        std::cin >> newEnemy.mana;
    }
    std::cout << "New Enemy gold: ";
    std::cin >> newEnemy.gold;
    while (newEnemy.gold <= 0) {
        std::cout << "gold must be greater than 0\n" << "Enter new enemy gold: ";
        std::cin >> newEnemy.gold;
    }

    return newEnemy;
}

void ShowEnemies(const std::vector<Character>& enemies) {
    std::cout << "\n=== Enemy list ===\n";
    for (const Character& currentEnemy : enemies)
    {
        std::cout << currentEnemy.name << " - health: "
            << currentEnemy.health
            << "\n";
    }
}

std::size_t ChooseEnemy(const std::vector<Character>& enemies)
{
    int enemyChoice;

    std::cout << "Choose your enemy 1-" << enemies.size() << " : ";
    std::cin >> enemyChoice;

    while (enemyChoice < 1 || enemyChoice > static_cast<int>(enemies.size()))
    {
        std::cout << "Choose a number from 1 to "
            << enemies.size() << ": ";
        std::cin >> enemyChoice;
    }
    
    return static_cast<std::size_t>(enemyChoice - 1);
}

bool Fight(Character& player, Character& enemy) 
{
    int damage;
    int round = 1;
    int enemyDamage = 10;
    while (enemy.health > 0 && player.health > 0)
    {
        std::cout << "\n=== Round " << round << " ===\n";

        

        std::cout << "Enter damage to " << enemy.name << ": ";
        std::cin >> damage;
        while (damage <= 0)
        {
            std::cout << "Damage must be greater than 0. Enter again: ";
            std::cin >> damage;
        }

        ApplyDamage(enemy, damage);
        ShowStatus(enemy);
        std::cout << enemy.name << " health: " << enemy.health << "\n";

        if (enemy.health > 0) {
            std::cout << enemy.name << " attacks for " << enemyDamage << " damage.\n";
            ApplyDamage(player, enemyDamage);
            ShowStatus(player);

        }

        std::cout << player.name << " health: " << player.health << "\n";


        round++;
    }

    return player.health > 0;
}

int main()
{
    Character player{};

    std::vector<Character> enemies
    {
        {"Goblin", 3, 60, 0, 25},
        {"Orc", 5, 100, 0, 40},
        {"Mage", 7, 80, 100, 70}
    };
    
    enemies.push_back(CreateEnemy());
    
    ShowEnemies(enemies);
    
    std::cout << "\nEnter player name: ";
    std::cin >> player.name;

    std::cout << "Enter player level: ";
    std::cin >> player.level;

    std::cout << "Enter player health: ";
    std::cin >> player.health;

    std::cout << "Enter player mana: ";
    std::cin >> player.mana;

    std::cout << "Enter player gold: ";
    std::cin >> player.gold;

    std::size_t enemyIndex = ChooseEnemy(enemies);
    Character& enemy = enemies[enemyIndex];

    int spellCost = 20;

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

    bool playerWon = Fight(player, enemy);

    if (playerWon)
    {
        std::cout <<"\n" << player.name << " WINS!\n";
        player.gold = player.gold + enemy.gold;
        std::cout << "\nReward: "<< enemy.gold <<" gold!\n";
        enemy.gold = 0;
    }
    else
    {
        std::cout <<"\n" << enemy.name << " WINS!\n";
        std::cout << "\nYou don't receive reward!";
    }

    ShowProfile(player);
    ShowProfile(enemy);

    std::cout << "\n=== Enemies after battle ===\n";
    for (const Character& currentEnemy : enemies)
    {
        std::cout << currentEnemy.name
            << " - health: " << currentEnemy.health
            << ", gold: " << currentEnemy.gold
            << "\n";
    }


    return 0;

}