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

struct GameState
{
    Character player;
    std::vector<Character> companions;
    std::vector<Character> enemies;
    bool isRunning = true;
};

enum class MainMenuAction
{
    ShowParty = 1,
    ShowEnemies = 2,
    AddEnemy = 3,
    RemoveEnemy = 4,
    StartBattle = 5,
    Exit = 6
};

enum class Action
{
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

std::string ReadLine(const std::string& prompt)
{
    while (true)
    {
        std::string value;

        std::cout << prompt;
        std::getline(std::cin >> std::ws, value);

        if (!value.empty())
        {
            return value;
        }

        std::cout << "Input cannot be empty.\n";
    }
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

void ShowStatus(const Character& character)
{
    if (character.health <= 0)
    {
        std::cout << "\n"
            << character.name
            << " Status: Dead\n";
    }
    else if (character.health <= 25)
    {
        std::cout << "\n"
            << character.name
            << " Status: Critical\n";
    }
    else
    {
        std::cout << "\n"
            << character.name
            << " Status: Alive\n";
    }
}

void ShowEnemies(const std::vector<Character>& enemies)
{
    std::cout << "\n=== Enemy List ===\n";

    if (enemies.empty())
    {
        std::cout << "No enemies available.\n";
        return;
    }

    for (std::size_t i = 0; i < enemies.size(); i++)
    {
        const Character& enemy = enemies[i];

        std::cout << i + 1
            << ". "
            << enemy.name
            << " - Health: "
            << enemy.health
            << "/"
            << enemy.maxHealth
            << ", Gold: "
            << enemy.gold
            << "\n";
    }
}

void ShowParty(
    const Character& player,
    const std::vector<Character>& companions
)
{
    std::cout << "\n=== Party ===\n";

    std::cout << "\n=== Player ===\n";
    ShowProfile(player);

    std::cout << "\n=== Companions ===\n";

    for (const Character& companion : companions)
    {
        ShowProfile(companion);
    }
}

void ShowMainMenu()
{
    std::cout << "\n=== Main Menu ===\n";
    std::cout << "1. Show party\n";
    std::cout << "2. Show enemies\n";
    std::cout << "3. Add enemy\n";
    std::cout << "4. Remove enemy\n";
    std::cout << "5. Start battle\n";
    std::cout << "6. Exit\n";
}

void ShowBattleMenu()
{
    std::cout << "\n=== Battle Menu ===\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Cast spell\n";
    std::cout << "3. Heal\n";
    std::cout << "4. Exit\n";
}

Character CreatePlayer()
{
    Character newPlayer{};

    newPlayer.name =
        ReadLine("\nEnter player name: ");

    newPlayer.level =
        ReadInt("Enter player level: ", 1);

    newPlayer.maxHealth =
        ReadInt("Enter player max health: ", 1);

    newPlayer.health = newPlayer.maxHealth;

    newPlayer.mana =
        ReadInt("Enter player mana: ", 0);

    newPlayer.gold =
        ReadInt("Enter player gold: ", 0);

    return newPlayer;
}

Character CreateEnemy()
{
    Character newEnemy{};

    newEnemy.name =
        ReadLine("\nEnter new enemy name: ");

    newEnemy.level =
        ReadInt("Enter new enemy level: ", 1);

    newEnemy.maxHealth =
        ReadInt("Enter new enemy max health: ", 1);

    newEnemy.health = newEnemy.maxHealth;

    newEnemy.mana =
        ReadInt("Enter new enemy mana: ", 0);

    newEnemy.gold =
        ReadInt("Enter new enemy gold: ", 0);

    return newEnemy;
}

std::vector<Character> CreateDefaultCompanions()
{
    return {
        {"DPS", 10, 100, 100, 50, 200},
        {"TANK", 10, 200, 200, 30, 100},
        {"HEALER", 10, 60, 60, 100, 150}
    };
}

std::vector<Character> CreateDefaultEnemies()
{
    return {
        {"Goblin", 3, 60, 60, 0, 25},
        {"Orc", 5, 100, 100, 0, 40},
        {"Mage", 7, 80, 80, 100, 70}
    };
}

GameState CreateGame()
{
    GameState game{
        CreatePlayer(),
        CreateDefaultCompanions(),
        CreateDefaultEnemies()
    };

    return game;
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
        std::cout
            << "Heal amount must be greater than 0.\n";

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

MainMenuAction ReadMainMenuAction()
{
    ShowMainMenu();

    int choice =
        ReadIntRange("Choose option: ", 1, 6);

    return static_cast<MainMenuAction>(choice);
}

Action ReadAction()
{
    ShowBattleMenu();

    int choice =
        ReadIntRange("Choose action: ", 1, 4);

    return static_cast<Action>(choice);
}

std::size_t ChooseEnemy(
    const std::vector<Character>& enemies
)
{
    int maxChoice = static_cast<int>(enemies.size());

    int enemyChoice = ReadIntRange("Choose your enemy 1-"+ std::to_string(maxChoice)+ ": ", 1, maxChoice);

    return static_cast<std::size_t>(enemyChoice - 1);
}

void RemoveEnemy(
    GameState& game
)
{
    if (game.enemies.empty())
    {
        std::cout <<
            "Enemy list is empty.\n";
        return;
    }

    ShowEnemies(game.enemies);

    std::size_t enemyIndex = ChooseEnemy(game.enemies);
  
    std::cout << game.enemies[enemyIndex].name << " has been removed from the list.\n";
    game.enemies.erase(game.enemies.begin() + enemyIndex);
}

BattleResult Fight(
    Character& player,
    Character& enemy
)
{
    int round = 1;

    const int enemyDamage = 10;
    const int spellCost = 20;
    const int spellDamage = 25;
    const int healAmount = 30;

    while (enemy.health > 0 && player.health > 0)
    {
        std::cout << "\n=== Round "
            << round
            << " ===\n";

        Action action = ReadAction();

        bool actionSucceeded = false;

        switch (action)
        {
        case Action::Attack:
        {
            int damage = ReadInt(
                "Enter damage to "
                + enemy.name
                + ": ",
                1
            );

            ApplyDamage(enemy, damage);
            actionSucceeded = true;

            ShowStatus(enemy);

            std::cout << enemy.name
                << " health: "
                << enemy.health
                << "/"
                << enemy.maxHealth
                << "\n";

            break;
        }

        case Action::CastSpell:
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
                << "/"
                << enemy.maxHealth
                << "\n";

            std::cout << player.name
                << " mana: "
                << player.mana
                << "\n";

            actionSucceeded = true;
            break;

        case Action::Heal:
            if (!Heal(player, healAmount))
            {
                break;
            }

            std::cout << player.name
                << " heals.\n";

            std::cout << player.name
                << " health: "
                << player.health
                << "/"
                << player.maxHealth
                << "\n";

            actionSucceeded = true;
            break;

        case Action::Exit:
            std::cout
                << "Player left the battle.\n";

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
            << "/"
            << player.maxHealth
            << "\n";

        round++;
    }

    if (player.health > 0)
    {
        return BattleResult::Victory;
    }

    return BattleResult::Defeat;
}

void ProcessBattleResult(
    GameState& game,
    BattleResult battleResult,
    std::size_t enemyIndex
)
{
    Character& enemy =
        game.enemies[enemyIndex];

    switch (battleResult)
    {
    case BattleResult::Victory:
    {
        const int reward = enemy.gold;

        std::cout << "\n"
            << game.player.name
            << " WINS!\n";

        game.player.gold += reward;

        std::cout << "Reward: "
            << reward
            << " gold!\n";

        enemy.gold = 0;

        ShowProfile(enemy);

        game.enemies.erase(
            game.enemies.begin() + enemyIndex
        );

        if (game.enemies.empty())
        {
            std::cout
                << "\nAll enemies have been defeated!\n";
        }

        break;
    }

    case BattleResult::Defeat:
        std::cout << "\n"
            << enemy.name
            << " WINS!\n";

        std::cout
            << "You don't receive a reward!\n";

        std::cout << "Game over.\n";

        ShowProfile(enemy);

        game.isRunning = false;
        break;

    case BattleResult::Escaped:
        std::cout
            << "\nYou escaped from the battle.\n";

        break;
    }
}

void StartBattle(GameState& game)
{
    if (game.enemies.empty())
    {
        std::cout << "No enemies available.\n";
        return;
    }

    if (game.player.health <= 0)
    {
        std::cout
            << "The player is dead and cannot fight.\n";

        return;
    }

    ShowEnemies(game.enemies);

    std::size_t enemyIndex =
        ChooseEnemy(game.enemies);

    Character& enemy =
        game.enemies[enemyIndex];

    ShowProfile(game.player);
    ShowProfile(enemy);

    const int spellCost = 20;

    if (CanCastSpell(game.player.mana, spellCost))
    {
        std::cout << "\nMagic: Spell ready\n";
    }
    else
    {
        std::cout
            << "\nMagic: Not enough mana!\n";
    }

    std::cout << "\nBattle starts in:\n";

    for (int i = 3; i >= 1; i--)
    {
        std::cout << i << "\n";
    }

    std::cout << "Fight!\n";

    BattleResult battleResult =
        Fight(game.player, enemy);

    ProcessBattleResult(
        game,
        battleResult,
        enemyIndex
    );
}

void ProcessMainMenuAction(
    GameState& game,
    MainMenuAction action
)
{
    switch (action)
    {
    case MainMenuAction::ShowParty:
        ShowParty(
            game.player,
            game.companions
        );
        break;

    case MainMenuAction::ShowEnemies:
        ShowEnemies(game.enemies);
        break;

    case MainMenuAction::AddEnemy:
        game.enemies.push_back(
            CreateEnemy()
        );

        std::cout << "Enemy added.\n";
        break;

    case MainMenuAction::RemoveEnemy:
        RemoveEnemy(game);
        break;

    case MainMenuAction::StartBattle:
        StartBattle(game);
        break;

    case MainMenuAction::Exit:
        game.isRunning = false;
        break;
    }
}

void RunMainMenu(GameState& game)
{
    while (game.isRunning)
    {
        MainMenuAction action =
            ReadMainMenuAction();

        ProcessMainMenuAction(
            game,
            action
        );
    }

    std::cout << "Game closed.\n";
}

void RunGame()
{
    std::cout
        << "=== Welcome to the Battle Game ===\n";

    std::cout << std::boolalpha;

    GameState game = CreateGame();

    RunMainMenu(game);
}

int main()
{
    RunGame();
}