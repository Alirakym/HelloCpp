#include <iostream>
#include <string>
#include <vector>
#include <limits>

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

int ReadInt(const std::string& prompt, int minValue)
{
    int value;

    while (true)
    {
        std::cout << prompt;

        if (std::cin >> value && value >= minValue)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        if (std::cin.fail())
        {
            std::cout << "Enter a valid number.\n";
            std::cin.clear();
        }
        else
        {
            std::cout << "Value must be at least " << minValue << ".\n";
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
}

Character CreatePlayer()
{
    Character newPlayer{};
    std::cout << "Enter player name: ";
    std::cin >> newPlayer.name;

    newPlayer.level = ReadInt("Enter player level: ", 1);
    newPlayer.health = ReadInt("Enter player health: ", 1);
    newPlayer.mana = ReadInt("Enter player mana: ", 0);
    newPlayer.gold = ReadInt("Enter player gold: ", 0);
    return newPlayer;
}

Character CreateEnemy() 
{
    Character newEnemy{};

    std::cout << "Enter New Enemy name: ";
    std::cin >> newEnemy.name;

    newEnemy.level = ReadInt("Enter new enemy level: ", 1);
    newEnemy.health = ReadInt("Enter new enemy health: ", 1);
    newEnemy.mana = ReadInt("Enter new enemy mana: ", 0);
    newEnemy.gold = ReadInt("Enter new enemy gold: ", 0);
    return newEnemy;
}

void ShowEnemies(const std::vector<Character>& enemies) {
    std::cout << "\n=== Enemy list ===\n";
    for (const Character& currentEnemy : enemies)
    {
        std::cout << currentEnemy.name
            << " - health: " << currentEnemy.health
            << ", gold: " << currentEnemy.gold
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
    int round = 1;
    int enemyDamage = 10;
    while (enemy.health > 0 && player.health > 0)
    {
        std::cout << "\n=== Round " << round << " ===\n";

        int damage = ReadInt(
            "Enter damage to " + enemy.name + ": ",
            1
        );

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
    Character player = CreatePlayer(); 

    std::vector<Character> enemies
    {
        {"Goblin", 3, 60, 0, 25},
        {"Orc", 5, 100, 0, 40},
        {"Mage", 7, 80, 100, 70}
    };
    
    enemies.push_back(CreateEnemy());
    
    ShowEnemies(enemies);

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
    ShowEnemies(enemies);


    return 0;

}