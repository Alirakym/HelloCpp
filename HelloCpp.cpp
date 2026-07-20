#include <iostream>
#include <string>

int main()
{
    std::string playerName;
    int playerLevel;
    int playerHealth;
    int playerMana;
    int playerGold;
    int damage;
    int round = 1;

    std::cout << "Enter player name: ";
    std::cin >> playerName;

    std::cout << "Enter player level: ";
    std::cin >> playerLevel;

    std::cout << "Enter player health: ";
    std::cin >> playerHealth;

    std::cout << "Enter player mana: ";
    std::cin >> playerMana;

    std::cout << "Enter player gold: ";
    std::cin >> playerGold;

    if (playerMana >= 20)
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

    while (playerHealth > 0)
    {
        std::cout << "\n=== Round " << round << " ===\n";

        
        std::cout << "Enter damage: ";
        std::cin >> damage;
        while (damage <= 0)
        {
            std::cout << "Damage must be greater than 0. Enter again: ";
            std::cin >> damage;
        }

        playerHealth = playerHealth - damage;

        if (playerHealth <= 0)
        {
            playerHealth = 0;
            std::cout << "\nStatus: Dead\n";
        }
        else if (playerHealth <= 25)
        {
            std::cout << "\nStatus: Critical\n";
        }
        else
        {
            std::cout << "\nStatus: Alive\n";
        }
        
        std::cout << "Current health: " << playerHealth << "\n";

        round = round + 1;
    }

    
    std::cout << "\n === Character Profile === \n";
    std::cout <<" Name: " << playerName << '\n';
    std::cout << " Level: " << playerLevel << '\n';
    std::cout << " Mana: " << playerMana << '\n';
    std::cout << " Gold: " << playerGold << '\n';
    std::cout << " Health after damage: " << playerHealth << '\n';

    return 0;
}