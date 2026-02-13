/*
 * Class Player, derived from Character, representing the player-controlled character in the game.
 * Contains player-specific attributes like level and experience, as well as methods for handling input, attacking enemies, and leveling up.
 * Overrides damage calculation to reflect different weapons or abilities compared to enemies.
*/
#pragma once

#include "Character.h"
#include "../systems/inventory/Inventory.h"

class Enemy;

class Player : public Character {
private:
    int level;
    int experience;
    Inventory* inventory;

public:
    Player(const char* texturesheet, SDL_Renderer* ren, float startX, float startY);
    ~Player();

    void update(float deltaTime) override;
    void handleInput(float deltaTime);

    // Player-specific combat
    void attack(Enemy* enemy);
    void gainExperience(int xp);

    // Override damage calculation for different weapon
    int rollDamage() const override;

    // Inventory methods
    void useHealthPotion();
    Inventory* getInventory() { return inventory; }

    // Getters
    int getLevel() const { return level; }
    int getExperience() const { return experience; }

private:
    void levelUp();
    int getXPForNextLevel() const;
};