// systems/ai/EnemyAI.cpp
#include "EnemyAI.h"
#include "../../entities/Enemy.h"
#include "../../entities/Player.h"
#include "../../entities/Character.h"
#include <cmath>
#include <cstdlib>

EnemyAI::EnemyAI(float detection, float aggro, float fleeHP)
    : currentState(AIState::IDLE),
      detectionRange(detection),
      aggroRange(aggro),
      fleeHealthPercent(fleeHP) {}

void EnemyAI::update(float deltaTime, Enemy* self, Player* player) {
    if (!self || self->getIsDead()) {
        currentState = AIState::DEAD;
        return;
    }
    
    if (!player) return;
    
    // Update state transitions
    updateStateTransitions(self, player);
    
    // Execute current state behavior
    switch (currentState) {
        case AIState::IDLE:
            idleBehavior(deltaTime, self);
            break;
        case AIState::PATROL:
            patrolBehavior(deltaTime, self);
            break;
        case AIState::CHASE:
            chaseBehavior(deltaTime, self, player);
            break;
        case AIState::ATTACK:
            attackBehavior(deltaTime, self, player);
            break;
        case AIState::FLEE:
            fleeBehavior(deltaTime, self, player);
            break;
        case AIState::DEAD:
            break;
    }
}

void EnemyAI::updateStateTransitions(Enemy* self, Player* player) {
    float distToPlayer = getDistanceToPlayer(self, player);
    
    // Check if should flee (low HP)
    if (shouldFlee(self) && currentState != AIState::FLEE && currentState != AIState::DEAD) {
        currentState = AIState::FLEE;
        return;
    }
    
    switch (currentState) {
        case AIState::IDLE:
            // Random patrol chance
            if (rand() % 100 < 2) { // 2% chance per frame
                currentState = AIState::PATROL;
            }
            // Detect player
            if (distToPlayer < detectionRange) {
                currentState = AIState::CHASE;
            }
            break;
            
        case AIState::PATROL:
            // Detect player
            if (distToPlayer < detectionRange) {
                currentState = AIState::CHASE;
            }
            // Random stop patrolling
            if (rand() % 100 < 1) {
                currentState = AIState::IDLE;
            }
            break;
            
        case AIState::CHASE:
            // In attack range
            if (distToPlayer <= self->getAttackRange()) {
                currentState = AIState::ATTACK;
            }
            // Lost player
            if (distToPlayer > aggroRange) {
                currentState = AIState::IDLE;
            }
            break;
            
        case AIState::ATTACK:
            // Player moved away
            if (distToPlayer > self->getAttackRange() * 1.5f) {
                currentState = AIState::CHASE;
            }
            break;
            
        case AIState::FLEE:
            // Safe distance reached
            if (distToPlayer > aggroRange * 2.0f) {
                currentState = AIState::IDLE;
            }
            break;
            
        case AIState::DEAD:
            break;
    }
}

void EnemyAI::idleBehavior(float deltaTime, Enemy* self) {
    self->setSpeed(0, 0);
}

void EnemyAI::patrolBehavior(float deltaTime, Enemy* self) {
    // Simple left-right patrol
    if (self->getFacing() == Character::LEFT) {
        self->setSpeed(-50.0f, 0);
        if (self->getX() < 100) self->setFacing(Character::RIGHT);
    } else {
        self->setSpeed(50.0f, 0);
        if (self->getX() > 700) self->setFacing(Character::LEFT);
    }
}

void EnemyAI::chaseBehavior(float deltaTime, Enemy* self, Player* player) {
    if (!player) return;
    self->moveTowards(player->getX(), player->getY(), deltaTime);
}

void EnemyAI::attackBehavior(float deltaTime, Enemy* self, Player* player) {
    if (!player) return;
    
    self->setSpeed(0, 0);
    self->attackTarget(player);
}

void EnemyAI::fleeBehavior(float deltaTime, Enemy* self, Player* player) {
    if (!player) return;
    
    // Move away from player
    float dx = self->getX() - player->getX();
    float dy = self->getY() - player->getY();
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance > 0) {
        float moveSpeed = self->getBaseSpeed() * 1.5f; // Flee faster
        self->setSpeed((dx / distance) * moveSpeed, (dy / distance) * moveSpeed);
    }
}

float EnemyAI::getDistanceToPlayer(Enemy* self, Player* player) const {
    return self->distanceTo(player->getX(), player->getY());
}

bool EnemyAI::shouldFlee(Enemy* self) const {
    float healthPercent = static_cast<float>(self->getCurrentHP()) / self->getMaxHP();
    return healthPercent <= fleeHealthPercent;
}