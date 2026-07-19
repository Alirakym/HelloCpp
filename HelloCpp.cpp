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

    std::cout << "Enter damage: ";
    std::cin >> damage;

    playerHealth = playerHealth - damage;

    std::cout << "\n === Character Profile === \n";
    std::cout <<" Name: " << playerName << '\n';
    std::cout << " Level: " << playerLevel << '\n';
    std::cout << " Mana: " << playerMana << '\n';
    std::cout << " Gold: " << playerGold << '\n';
    std::cout << " Health after damage: " << playerHealth << '\n';

    return 0;
}