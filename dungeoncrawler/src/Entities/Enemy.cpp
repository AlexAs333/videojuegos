#include "Enemy.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

// Constructor
Enemy::Enemy(const string& enemyName, float startX, float startY)
	: name(enemyName), x(startX), y(startY),
	speedX(0), speedY(0), speed(100.0f),
	facing(DOWN), currentState(IDLE),
	isDead(false), lastAttackTime(0.0f)
{
	// default values (children may modify)
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

	detectionRange = 200.0f;
	attackRange = 50.0f;
	attackCooldown = 1.5f;

	experienceValue = 50;

	// basic hitBox
	hitbox = { (int)x, (int)y, 32, 32 };

	// debug color (red)
	debugColor = { 255,0,0,255 };
}

Enemy::~Enemy() {
	// cleanup if needed
}

// main update
void Enemy::update(float deltaTime, Player* player) {
	if (isDead) return;

	// update AI
	updateAI(deltaTime, player);

	// apply speed
	x += speedX * deltaTime;
	y += speedY * deltaTime;

	// update hitbox
	updateHitbox();

	// down speed
	speedX *= 0.9f;
	speedY *= 0.9f;
}

// main AI
void Enemy::updateAI(float deltaTime, Player* player) {
	if (!player) return;

	// TODO: Check when player
	float distanceToPlayer = distanceTo(player->getX(), player->getY());

	// FSM 
	switch (currentState) {
		case IDLE:
			idleBehavior(deltaTime);
			// transition to chase if detects player
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
		case ATTACK:
			attackBehavior(deltaTime, player);
			// hysteresis: exit attack only beyond +20% range to avoid state flicker
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
			// X(
			break;
	}	
}


// AI Behaviors
void Enemy::idleBehavior(float deltaTime) {
	// default
	speedX = 0;
	speedY = 0;
}

void Enemy::chaseBehavior(float deltaTime, Player* player) {
	if (!player) return;
	moveTowards(player->getX(), player->getY(), deltaTime);
}

void Enemy::attackBehavior(float deltaTime, Player* player) {
	if (!player) return;

	// stop when attacking
	speedX = 0;
	speedY = 0;

	// look to player
	float dx = player->getX() - x;
	float dy = player->getY() - y;
	if (abs(dx) > abs(dy)) facing = (dx > 0) ? RIGHT : LEFT;
	else facing = (dy > 0) ? DOWN : UP;

	// attacks cooldown
	lastAttackTime += deltaTime;
	if (lastAttackTime >= attackCooldown) {
		attack(player);
		lastAttackTime = 0.0f;
	}
}

void Enemy::fleeBehavior(float deltaTime, Player* player) {
	if (!player) return;

	// move opposite to player 
	float dx = x - player->getX();
	float dy = y - player->getY();
	float distance = sqrt(dx * dx + dy * dy);

	if (distance > 0) {
		speedX = (dx / distance) * speed;
		speedY = (dy / distance) * speed;
	}
}

// Combat
void Enemy::attack(Player* player) {
	int attackRoll = rollAttack();

	if (attackRoll >= player->getArmorClass()) {
		// Impacto: hacer daño
		int damage = rollDamage();
		player->takeDamage(damage);
	}
}

void Enemy::takeDamage(int damage) {
	if (isDead) return;

	currentHP -= damage;

	if (currentHP <= 0) {
		currentHP = 0;
		die();
	}
}

void Enemy::die() {
	isDead = true;
	currentState = DEAD;
}

// Movement
void Enemy::move(float dx, float dy) {
	speed = dx;
	speedY = dy;
}

void Enemy::moveTowards(float targetX, float targetY, float deltaTime) {
	float dx = targetX - x;
	float dy = targetY - y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance > 0) {
		// normalize and apply speed
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

float Enemy::distanceTo(float targetX, float targetY) const {
	float dx = targetX - x;
	float dy = targetY - y;
	return sqrt(dx * dx + dy * dy);
}

// D&D 5e calcs
int Enemy::getMod(int stat) const {
	return (stat - 10) / 2;
}

int Enemy::rollAttack() const {
	// d20 + relevant stat + proficiency bonus
	int d20 = (rand() % 20) + 1;
	int attackBonus = getMod(strength) + proficiencyBonus;
	return d20 + attackBonus;
}

int Enemy::rollDamage() const {
	// basic: 1d6 + str modifier (punch)
	// children may modify
	int d6 = (rand() % 6) + 1;
	return d6 + getMod(strength);
}

bool Enemy::rollSavingThrow(const std::string& ability, int DC) const {
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

// rendering
void Enemy::render(SDL_Renderer* renderer) {
	if (isDead) return;

	// debug: render as red rectangle
	SDL_SetRenderDrawColor(renderer, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
	SDL_RenderFillRect(renderer, &hitbox);

	// hp bar
	SDL_Rect healthBarBG = { (int)x, (int)y - 10, hitbox.w, 5 };
	SDL_Rect healthBarFG = { (int)x, (int)y - 10,
							(int)(hitbox.w * ((float)currentHP / maxHP)), 5 };

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(renderer, &healthBarBG);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &healthBarFG);
}

// aux
void Enemy::updateHitbox() {
	hitbox.x = (int)x;
	hitbox.y = (int)y;
}

bool Enemy::checkCollision(const SDL_Rect& other) const {
	return SDL_HasIntersection(&hitbox, &other);
}
