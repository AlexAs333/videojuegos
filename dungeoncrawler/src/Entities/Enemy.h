#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

using namespace std;

// forward declarations
class Player {
	float x, y; // Player position
public:
	float getX() const { return x; }
	float getY() const { return y; }
	int getArmorClass() const { return 15; } // Placeholder
	int getCurrentHP() const { return 100; } // Placeholder
	void takeDamage(int damage) { /* Placeholder */ }
};

class Enemy {
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
	int armorClass;	// AC
	int proficiencyBonus;

	// Position and movement
	float x, y;		// Current position
	float speedX, speedY;
	float speed;    // Base movement speed in pixels per frame

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	Direction facing; // Direction the enemy is currently facing (for animations and attacks)

	// AI state 
	enum AIState {
		IDLE,
		PATROL,
		CHASE,
		ATTACK,
		FLEE,
		DEAD
	};
	AIState currentState;

	float detectionRange; // Player detection range
	float attackRange;    // Melee attack range
	float attackCooldown; // Time between attacks
	float lastAttackTime;

	// Render 
	SDL_Rect hitbox;
	SDL_Color debugColor;

	// general info
	string name;
	int experienceValue; // XP given to player when defeated
	bool isDead; // X(

public: 
	// cons and dest
	Enemy(const string& name, float startX, float startY);
	virtual ~Enemy();

	// Main methods (virtual for override)
	virtual void update(float deltaTime, Player* player);
	virtual void render(SDL_Renderer* renderer);
	virtual void takeDamage(int damage);
	virtual void attack(Player* player);

	// AI (virtual for archeotypes: melee, ranged, caster)
	virtual void updateAI(float deltaTime, Player* player);
	virtual void idleBehavior(float deltaTime);
	virtual void patrolBehavior(float deltaTime);
	virtual void chaseBehavior(float deltaTime, Player* player);
	virtual void attackBehavior(float deltaTime, Player* player);
	virtual void fleeBehavior(float deltaTime, Player* player);

	// Movement and util
	void move(float dx, float dy);
	void moveTowards(float targetX, float targetY, float deltaTime);
	float distanceTo(float targetX, float targetY) const;

	// D&D calcs
	int getMod(int stat) const; // calcs modifier from stat (e.g. 10-11 = +0, 12-13 = +1, etc.)
	int rollAttack() const;		// rolls an attack (d20 + proficiency + relevant mod) if attack roll > AC -> hit
	int rollDamage() const;		// rolls damage 
	bool rollSavingThrow(const string& abilty, int DC) const; // rolls a saving throw against DC (e.g. for spells or traps)

	// Getters
	float getX() const { return x; }
	float getY() const { return y; }
	bool getIsDead() const { return isDead; }
	int getCurrentHP() const { return currentHP; }
	int getMaxHP() const { return maxHP; }
	AIState getState() const { return currentState; }
	SDL_Rect getHitbox() const { return hitbox; }
	int getExperienceValue() const { return experienceValue; }

	// Setters
	void setState(AIState newState) { currentState = newState; }

	// colisions
	bool checkCollision(const SDL_Rect& other) const;

protected: 
	// aux methods
	void updateHitbox();
	void die();
};