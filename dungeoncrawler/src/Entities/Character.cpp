#include "Character.h"
#include <cmath>
#include <cstdlib>

Character::Character(const string& charName, const char* texturesheet, SDL_Renderer* ren, float startX, float startY)
    : GameObject(texturesheet, ren, (int)startX, (int)startY),
    name(charName), x(startX), y(startY),
    speedX(0), speedY(0), speed(100.0f),
    facing(DOWN), lastAttackTime(0.0f), isDead(false)
{

    if (objTexture == nullptr) {
        std::cout << "WARNING: " << name << " no tiene textura cargada!" << std::endl;
    } else {
        std::cout << "OK: " << name << " textura cargada correctamente" << std::endl;
    }
    // GameObject already loaded texture and initialized rects
    hitbox = {(int)x, (int)y, 64, 64};
    
    // Default stats
    strength = 10;
    dexterity = 10;
    constitution = 10;
    intelligence = 10;
    wisdom = 10;
    charisma = 10;

    maxHP = 20;
    currentHP = maxHP;
    armorClass = 10;
    proficiencyBonus = 2;

    attackRange = 50.0f;
    attackCooldown = 1.0f;

    debugColor = {255, 255, 255, 255};
}

Character::~Character() {}

void Character::render() {
    if (isDead) return;

    // Call base GameObject render for sprite
    GameObject::render();

    // Add HP bar
    SDL_Rect healthBarBG = {destRect.x, destRect.y - 10, destRect.w, 5};
    SDL_Rect healthBarFG = {destRect.x, destRect.y - 10,
                            (int)(destRect.w * ((float)currentHP / maxHP)), 5};

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &healthBarBG);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &healthBarFG);
}

void Character::takeDamage(int damage) {
    if (isDead) return;

    currentHP -= damage;

    if (currentHP <= 0) {
        currentHP = 0;
        die();
    }
}

void Character::die() {
    isDead = true;
}

void Character::attackTarget(Character* target) {
    if (!target || target->getIsDead()) return;
    if (lastAttackTime < attackCooldown) return;

    float distance = distanceTo(target->getX(), target->getY());
    if (distance > attackRange) return;

    int attackRoll = rollAttack();
    
    if (attackRoll >= target->getArmorClass()) {
        int damage = rollDamage();
        target->takeDamage(damage);
    }

    lastAttackTime = 0.0f;
}

void Character::move(float dx, float dy) {
    speedX = dx;
    speedY = dy;
}

void Character::moveTowards(float targetX, float targetY, float deltaTime) {
    float dx = targetX - x;
    float dy = targetY - y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        speedX = (dx / distance) * speed;
        speedY = (dy / distance) * speed;

        if (abs(dx) > abs(dy)) {
            facing = (dx > 0) ? RIGHT : LEFT;
        }
        else {
            facing = (dy > 0) ? DOWN : UP;
        }
    }
}

float Character::distanceTo(float targetX, float targetY) const {
    float dx = targetX - x;
    float dy = targetY - y;
    return sqrt(dx * dx + dy * dy);
}

// D&D calculations
int Character::getMod(int stat) const {
    return (stat - 10) / 2;
}

int Character::rollAttack() const {
    int d20 = (rand() % 20) + 1;
    int attackBonus = getMod(strength) + proficiencyBonus;
    return d20 + attackBonus;
}

int Character::rollDamage() const {
    int d6 = (rand() % 6) + 1;
    return d6 + getMod(strength);
}

bool Character::rollSavingThrow(const string& ability, int DC) const {
    int d20 = (rand() % 20) + 1;
    int modifier = 0;

    if (ability == "STR") modifier = getMod(strength);
    else if (ability == "DEX") modifier = getMod(dexterity);
    else if (ability == "CON") modifier = getMod(constitution);
    else if (ability == "INT") modifier = getMod(intelligence);
    else if (ability == "WIS") modifier = getMod(wisdom);
    else if (ability == "CHA") modifier = getMod(charisma);

    return (d20 + modifier) >= DC;
}

void Character::updateHitbox() {
    hitbox.x = (int)x;
    hitbox.y = (int)y;
    syncPositionToGameObject();
}

void Character::syncPositionToGameObject() {
    // Sync float positions to GameObject's int positions for rendering
    xpos = (int)x;
    ypos = (int)y;
    destRect.x = xpos;
    destRect.y = ypos;
}

bool Character::checkCollision(const SDL_Rect& other) const {
    return SDL_HasIntersection(&hitbox, &other);
}
