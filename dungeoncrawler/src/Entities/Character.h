/*
 * Class Character, derived from GameObject, representing a character in the game with D&D 5e stats and combat mechanics.
 * Contains attributes for D&D stats (STR, DEX, CON, INT, WIS, CHA), combat stats (HP, AC, proficiency bonus), and movement.
 * Implements methods for attacking, taking damage, moving, and calculating D&D mechanics like attack rolls and saving throws.
 * Also includes rendering of the character and a debug hitbox for collision detection.
 */ 
#pragma once

#include "GameObject.h"
#include <string>

using namespace std;

class Character : public GameObject {
protected:
    // D&D 5e stats
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    // Combat stats
    int maxHP;
    int currentHP;
    int armorClass;
    int proficiencyBonus;

    // Position and movement (float for smooth movement)
    float x, y;
    float speedX, speedY;
    float speed;


    // Attack
    float attackRange;
    float attackCooldown;
    float lastAttackTime;

    // Rendering
    SDL_Rect hitbox;
    SDL_Color debugColor;

    // General info
    string name;
    bool isDead;

public:
    Character(const string& charName, const char* texturesheet, SDL_Renderer* ren, float startX, float startY);
    virtual ~Character();

    // Override GameObject methods
    void update() override { update(0.016f); }  // Compatibility wrapper
    void render() override;
    
    // Main methods
    virtual void update(float deltaTime) = 0;
    virtual void takeDamage(int damage);

    // Combat
    void attackTarget(Character* target);

    // Movement
    void move(float dx, float dy);
    void moveTowards(float targetX, float targetY, float deltaTime);
    float distanceTo(float targetX, float targetY) const;

    // D&D calculations
    int getMod(int stat) const;
    virtual int rollAttack() const;
    virtual int rollDamage() const;
    bool rollSavingThrow(const string& ability, int DC) const;

    // Getters (override GameObject's getX/getY for float precision)
    float getX() const { return x; }
    float getY() const { return y; }
    int getCurrentHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getArmorClass() const { return armorClass; }
    SDL_Rect getHitbox() const { return hitbox; }
    bool getIsDead() const { return isDead; }
    string getName() const { return name; }

    // Collision
    bool checkCollision(const SDL_Rect& other) const;
    
    enum Direction {
        UP, DOWN, LEFT, RIGHT
    };
    Direction facing;

protected:
    void updateHitbox();
    void syncPositionToGameObject();  // Sync float x,y to GameObject's int xpos,ypos
    virtual void die();
};