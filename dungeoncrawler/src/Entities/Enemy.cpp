#include "Enemy.h"
#include "Player.h"
#include <cmath>

Enemy::Enemy(const string& enemyName, const char* texturesheet, SDL_Renderer* ren, float startX, float startY)
    : Character(enemyName, texturesheet, ren, startX, startY),
    currentState(IDLE), experienceValue(50)
{
    speed = 100.0f;
    detectionRange = 200.0f;
    attackRange = 50.0f;
    attackCooldown = 0.5f;
    debugColor = {255, 0, 0, 255};
}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime, Player* player) {
    if (isDead) return;

    // debug info 
    /*std::string stateName;
    switch (currentState) {
        case IDLE: stateName = "IDLE"; break;
        case PATROL: stateName = "PATROL"; break;
        case CHASE: stateName = "CHASE"; break;
        case ATTACK: stateName = "ATTACK"; break;
        case FLEE: stateName = "FLEE"; break;
        case DEAD: stateName = "DEAD"; break;
    }
    std::cout << "Enemy " << name << " state: " << stateName << std::endl;
    */

    updateAI(deltaTime, player);

    x += speedX * deltaTime;
    y += speedY * deltaTime;

    updateHitbox();

    speedX *= 0.9f;
    speedY *= 0.9f;

    lastAttackTime += deltaTime;
}

void Enemy::updateAI(float deltaTime, Player* player) {
    if (!player) return;

    float distanceToPlayer = distanceTo(player->getX(), player->getY());

    switch (currentState) {
        case IDLE:
            idleBehavior(deltaTime);
            // some chance to start patrolling
            if (rand() % 100 < 5) {
                currentState = PATROL;
            }
            if (distanceToPlayer < detectionRange) {
                currentState = CHASE;
            }
            break;

        case PATROL:
            patrolBehavior(deltaTime);
            if (distanceToPlayer < detectionRange) {
                currentState = CHASE;
            }
            break;

        case CHASE:
            chaseBehavior(deltaTime, player);
            if (distanceToPlayer <= attackRange) {
                currentState = ATTACK;
            }
            break;

        case ATTACK:
            attackBehavior(deltaTime, player);
            if (distanceToPlayer > attackRange * 1.2f) {
                currentState = CHASE;
            }
            break;

        case FLEE:
            fleeBehavior(deltaTime, player);
            if (distanceToPlayer > detectionRange * 2.0f) {
                currentState = IDLE;
            }
            break;

        case DEAD:
            break;
    }
}

void Enemy::idleBehavior(float deltaTime) {
    speedX = 0;
    speedY = 0;
}

void Enemy::patrolBehavior(float deltaTime) {
    // Simple back-and-forth patrol
    if (facing == LEFT) {
        speedX = -speed;
        if (x < 100) facing = RIGHT;
    } else {
        speedX = speed;
        if (x > 700) facing = LEFT;
    }
}

void Enemy::chaseBehavior(float deltaTime, Player* player) {
    if (!player) return;
    moveTowards(player->getX(), player->getY(), deltaTime);
}

void Enemy::attackBehavior(float deltaTime, Player* player) {
    if (!player) return;

    speedX = 0;
    speedY = 0;

    float dx = player->getX() - x;
    float dy = player->getY() - y;
    if (abs(dx) > abs(dy)) facing = (dx > 0) ? RIGHT : LEFT;
    else facing = (dy > 0) ? DOWN : UP;

    attackTarget(player);
}

void Enemy::fleeBehavior(float deltaTime, Player* player) {
    if (!player) return;

    float dx = x - player->getX();
    float dy = y - player->getY();
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        speedX = (dx / distance) * speed;
        speedY = (dy / distance) * speed;
    }
}

void Enemy::die() {
    Character::die();
    currentState = DEAD;
}