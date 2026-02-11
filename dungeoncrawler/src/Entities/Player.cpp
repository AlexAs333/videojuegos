#include "Player.h"
#include "Enemy.h"
#include "../core/InputHandler.h"

Player::Player(const char* texturesheet, SDL_Renderer* ren, float startX, float startY)
    : Character("Player", texturesheet, ren, startX, startY),
    level(1), experience(0)
{
    speed = 150.0f;
    
    // Better starting stats for player
    strength = 15;
    dexterity = 14;
    constitution = 13;
    intelligence = 10;
    wisdom = 12;
    charisma = 8;

    proficiencyBonus = 2;
    maxHP = 10 + getMod(constitution);
    currentHP = maxHP;
    armorClass = 10 + getMod(dexterity);

    attackCooldown = 1.0f;
    debugColor = {0, 255, 0, 255};
}

Player::~Player() {}

void Player::update(float deltaTime) {
    if (isDead) return;

    handleInput(deltaTime);

    x += speedX * deltaTime;
    y += speedY * deltaTime;

    updateHitbox();

    speedX *= 0.85f;
    speedY *= 0.85f;

    lastAttackTime += deltaTime;
}

void Player::handleInput(float deltaTime) {
    if (InputHandler::IsKeyDown(SDL_SCANCODE_W)) {
        speedY = -speed;
        facing = UP;
    }
    if (InputHandler::IsKeyDown(SDL_SCANCODE_S)) {
        speedY = speed;
        facing = DOWN;
    }
    if (InputHandler::IsKeyDown(SDL_SCANCODE_A)) {
        speedX = -speed;
        facing = LEFT;
    }
    if (InputHandler::IsKeyDown(SDL_SCANCODE_D)) {
        speedX = speed;
        facing = RIGHT;
    }
}

void Player::attack(Enemy* enemy) {
    if (!enemy || enemy->getIsDead()) return;
    
    attackTarget(enemy);
    
    if (enemy->getIsDead()) {
        gainExperience(enemy->getExperienceValue());
    }
}

void Player::gainExperience(int xp) {
    experience += xp;
    
    while (experience >= getXPForNextLevel()) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    proficiencyBonus = 2 + ((level - 1) / 4);
    
    int hpGain = (rand() % 10) + 1 + getMod(constitution);
    maxHP += hpGain;
    currentHP = maxHP;
    
    armorClass = 10 + getMod(dexterity);
}

int Player::getXPForNextLevel() const {
    return level * 100;
}

int Player::rollDamage() const {
    // Longsword: 1d8 + STR
    int d8 = (rand() % 8) + 1;
    return d8 + getMod(strength);
}