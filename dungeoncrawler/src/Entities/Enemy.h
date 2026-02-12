// entities/Enemy.h
#pragma once

#include "Character.h"
#include <memory>

class Player;
class EnemyAI;

class Enemy : public Character {
private:
    std::unique_ptr<EnemyAI> ai;
    int experienceValue;

public:
    Enemy(const string& name, const char* texturesheet, SDL_Renderer* ren, 
          float startX, float startY, EnemyAI* aiController);
    virtual ~Enemy();

    void update(float deltaTime) override { update(deltaTime, nullptr); }
    void update(float deltaTime, Player* player);

    // Getters
    int getExperienceValue() const { return experienceValue; }
    float getAttackRange() const { return attackRange; }
    float getBaseSpeed() const { return speed; }
    Character::Direction getFacing() const { return facing; }
    
    // Setters for AI control
    void setSpeed(float sx, float sy) { speedX = sx; speedY = sy; }
    void setFacing(Direction dir) { facing = dir; }
    void setExperienceValue(int xp) { experienceValue = xp; }

protected:
    void die() override;
};