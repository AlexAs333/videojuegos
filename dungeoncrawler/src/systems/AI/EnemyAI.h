// systems/ai/EnemyAI.h
#pragma once
#include <memory>

class Enemy;
class Player;

enum class AIState {
    IDLE,
    PATROL,
    CHASE,
    ATTACK,
    FLEE,
    DEAD
};

// Base abstract AI class
class EnemyAI {
protected:
    AIState currentState;
    float detectionRange;
    float aggroRange;      // Range at which enemy becomes hostile
    float fleeHealthPercent; // HP % at which enemy flees
    
public:
    EnemyAI(float detection = 200.0f, float aggro = 250.0f, float fleeHP = 0.2f);
    virtual ~EnemyAI() = default;
    
    // Main AI update loop
    virtual void update(float deltaTime, Enemy* self, Player* player);
    
    // State behaviors - can be overridden by derived classes
    virtual void idleBehavior(float deltaTime, Enemy* self);
    virtual void patrolBehavior(float deltaTime, Enemy* self);
    virtual void chaseBehavior(float deltaTime, Enemy* self, Player* player);
    virtual void attackBehavior(float deltaTime, Enemy* self, Player* player);
    virtual void fleeBehavior(float deltaTime, Enemy* self, Player* player);
    
    // State transitions - override for custom behavior
    virtual void updateStateTransitions(Enemy* self, Player* player);
    
    AIState getState() const { return currentState; }
    void setState(AIState newState) { currentState = newState; }
    
protected:
    float getDistanceToPlayer(Enemy* self, Player* player) const;
    bool shouldFlee(Enemy* self) const;
};