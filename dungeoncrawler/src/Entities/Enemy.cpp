// entities/Enemy.cpp
#include "Enemy.h"
#include "Player.h"
#include "../systems/ai/EnemyAI.h"

Enemy::Enemy(const string& enemyName, const char* texturesheet, SDL_Renderer* ren, 
             float startX, float startY, EnemyAI* aiController)
    : Character(enemyName, texturesheet, ren, startX, startY),
      ai(aiController),
      experienceValue(50)
{
    speed = 100.0f;
    attackRange = 50.0f;
    attackCooldown = 1.0f;
    debugColor = {255, 0, 0, 255};
}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime, Player* player) {
    if (isDead) return;

    // Update AI
    if (ai) {
        ai->update(deltaTime, this, player);
    }

    // Apply movement
    x += speedX * deltaTime;
    y += speedY * deltaTime;

    updateHitbox();

    // Friction
    speedX *= 0.9f;
    speedY *= 0.9f;

    lastAttackTime += deltaTime;
}

void Enemy::die() {
    Character::die();
}