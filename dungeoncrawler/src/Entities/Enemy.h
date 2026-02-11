/*
 * Class Enemy, derived from Character, representing an enemy in the game with basic AI behavior.
 * Differs from Player in that it has an AI state machine to determine its actions based on the player's position and its own state.
 * Includes states for idling, patrolling, chasing the player, attacking, fleeing, and being dead.
*/
#pragma once

#include "Character.h"

class Player;

class Enemy : public Character {
private:
    enum AIState {
        IDLE,
        PATROL,
        CHASE,
        ATTACK,
        FLEE,
        DEAD
    };
    AIState currentState;

    float detectionRange;
    int experienceValue;

public:
    Enemy(const string& name, const char* texturesheet, SDL_Renderer* ren, float startX, float startY);
    virtual ~Enemy();

    void update(float deltaTime) override { update(deltaTime, nullptr); }
    virtual void update(float deltaTime, Player* player);

    // AI methods
    virtual void updateAI(float deltaTime, Player* player);
    virtual void idleBehavior(float deltaTime);
    virtual void patrolBehavior(float deltaTime);
    virtual void chaseBehavior(float deltaTime, Player* player);
    virtual void attackBehavior(float deltaTime, Player* player);
    virtual void fleeBehavior(float deltaTime, Player* player);

    // Getters
    AIState getState() const { return currentState; }
    int getExperienceValue() const { return experienceValue; }

    void setState(AIState newState) { currentState = newState; }

protected:
    void die() override;
};