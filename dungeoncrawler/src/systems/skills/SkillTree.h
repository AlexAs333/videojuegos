/*
 * SkillTree file which defines the structure of the skill tree, including nodes and connections. 
 * Each node represents a skill that can be unlocked by the player, and connections define the dependencies between skills. 
*/
#pragma once
#include <vector>
#include <unordered_map>    // For storing nodes and connections
#include <unordered_set>    // For tracking unlocked skills
#include <string>
#include <memory>       

enum class SkillID {
    // COMMON SKILLS
    COOLDOWN_REDUCTION,

    // MAGE BRANCH - Common
    MAGE_ELDRITCH_BLAST,
    MAGE_ELDRITCH_BLAST_II,
    MAGE_ELDRITCH_BLAST_III,
    MAGE_ELDRITCH_BLAST_IV,
    MAGE_INTELLIGENCE_BOOST,

    // MAGE BRANCH - Fire
    MAGE_FIREBOLT,
    MAGE_FIREBOLT_II,
    MAGE_FIRE_RESISTANCE,
    MAGE_FIREBALL,
    MAGE_FIRE_SPELLS_BOOST,
    MAGE_NOVA,

    // MAGE BRANCH - Wind
    MAGE_AIR_SHIELD,
    MAGE_DEXTERITY_BOOST,
    MAGE_WIND,
    MAGE_COLD_RESISTANCE,
    MAGE_LIGHTNING,
    MAGE_WIND_SPELLS_BOOST,
    MAGE_ICE_STORM,

    // MAGE BRANCH - Nature
    MAGE_CURE_WOUNDS,
    MAGE_REMOVE_STATES,
    MAGE_CONSTITUTION_BOOST,
    MAGE_POISON_RESISTANCE,
    MAGE_TIDAL_WAVE,
    MAGE_NATURE_SPELLS_BOOST,
    MAGE_STONE_SKIN,

    // WARRIOR BRANCH - Common
    WARRIOR_SECOND_WIND,
    WARRIOR_SECOND_WIND_II,
    WARRIOR_SECOND_WIND_III,
    WARRIOR_SECOND_WIND_IV,

    // WARRIOR BRANCH - Defense
    WARRIOR_DEFENSIVE_STYLE,
    WARRIOR_CONSTITUTION_BOOST,
    WARRIOR_THORN_ARMOR,
    WARRIOR_THORN_ARMOR_II,
    WARRIOR_SHIELD,
    WARRIOR_AC_BOOST,
    WARRIOR_PHYSICAL_RESISTANCE,

    // WARRIOR BRANCH - Mixed
    WARRIOR_1AC_1OF,
    WARRIOR_MIXED_BOOST,
    WARRIOR_BLOCK,
    WARRIOR_BLOCK_AND_COUNTER,
    WARRIOR_AREA_ATTACK,
    WARRIOR_SPEED_BOOST,
    WARRIOR_ROLLING_DASH,

    // WARRIOR BRANCH - Offense
    WARRIOR_OFFENSIVE_STYLE,
    WARRIOR_STRENGTH_BOOST,
    WARRIOR_KNOCKBACK,
    WARRIOR_KNOCKBACK_II,
    WARRIOR_DASH,
    WARRIOR_DAMAGE_PRECISION_BOOST,
    WARRIOR_CRITICAL_HIT_ON_19,

    // ROGUE BRANCH - Common
    ROGUE_SNEAK_ATTACK,
    ROGUE_SNEAK_ATTACK_II,
    ROGUE_SNEAK_ATTACK_III,
    ROGUE_SNEAK_ATTACK_IV,

    // ROGUE BRANCH - Archery
    ROGUE_ARCHERY,
    ROGUE_WIS_DEX_BOOST,
    ROGUE_ARCHERY_II,
    ROGUE_PRECISION_BOOST,
    ROGUE_SHOTTING_MODES,
    ROGUE_HEEL_STRIKE,
    ROGUE_SKULL_SHOT,

    // ROGUE BRANCH - Bard
    ROGUE_HORROR_SONG,
    ROGUE_CHA_DEX_BOOST,
    ROGUE_COUNTER_SONG,
    ROGUE_LULLABY,
    ROGUE_RIPOSTE,
    ROGUE_HEALING_SONG,
    ROGUE_WAR_CRY,

    // ROGUE BRANCH - Assassin
    ROGUE_STEALTH,
    ROGUE_DEX_BOOST,
    ROGUE_POISON_PROBABILITY,
    ROGUE_DISARM,
    ROGUE_SPEED_BOOST,
    ROGUE_ROLLING_DASH,
    ROGUE_CRITICAL_HIT_ON_19,


    // MERGED BRANCH (WARRIOR/ROGUE) - Weapon Master
    WP_ATTACK_ROLL_BOOST,
    WP_DAMAGE_BOOST,

    // MERGED BRANCH (MAGE/ROGUE) - Warlock
    WARLOCK_TELEPORT,
    WARLOCK_ADD_CHA_BOOST,

    // MERGED BRANCH (MAGE/WARRIOR) - Paladin
    PALADIN_SMITE,
    PALADIN_AURA,

    NONE
}; 

enum class SkillBranch {
    COMMON,
    MAGE_COMMON,
    WARRIOR_COMMON,
    ROGUE_COMMON,
    MAGE_FIRE,
    MAGE_WIND,
    MAGE_NATURE,
    WARRIOR_DEFENSE,
    WARRIOR_MIXED,
    WARRIOR_OFFENSE,
    ROGUE_ARCHERY,
    ROGUE_BARD,
    ROGUE_ASSASSIN,
    PALADIN,
    WARLOCK,
    WEAPON_MASTER,
};

enum class DamageType {
    PHYSICAL,
    FIRE,
    COLD,
    LIGHTNING,
    FORCE,
    POISON,
    NECROTIC,
    RADIANT,
    PSYCHIC,
    THUNDER,
    NONE
};


struct SkillData {
    SkillID id;
    std::string name;
    std::string description;
    SkillBranch branch;

    // D&D 5e bonusses
    int damageDiceBonus;
    int damageDiceType;
    int flatDamageBonus;
    int acBonus;
    int hpBonus;
    int speedBonus;
    int attackSpeedBonus;
    float cooldownReduction; // Percentage reduction (e.g. 0.1 for 10%)
    float cooldown;
    int strBonus;
    int dexBonus;
    int conBonus;
    int intBonus;
    int wisBonus;
    std::string scalingStat; // "STR", "DEX", "CON", "INT", "WIS", "CHA"
    float fireSpellBonus;
    float windSpellBonus;
    float natureSpellBonus;
    int chaBonus;

    DamageType damageType;
    bool isPassive;
    bool grantsAbility;
    std::string abilityName;

    SkillData();
};

class SkillNode {
private:
    SkillData data;
    std::vector<SkillID> prerequisites;
    bool unlocked;

public:
    SkillNode(const SkillData& skillData, const std::vector<SkillID>& prereqs = {});

    const SkillData& getData() const { return data; }
    const std::vector<SkillID>& getPrerequisites() const { return prerequisites; }
    bool isUnlocked() const { return unlocked; }
    void unlock() { unlocked = true; }
    void lock() { unlocked = false; }
};

class SkillTree {
private:
    std::unordered_map<SkillID, std::unique_ptr<SkillNode>> skills;
    std::unordered_set<SkillID> unlockedSkills;
    int availablePoints;
    
    bool hasAllPrerequisites(SkillID skillId) const;
    void initializeSkills();

    void initializeCommonSkills();
    void initializeMageSkills();
    void initializeWarriorSkills();
    void initializeRogueSkills();
    void initializeMulticlassSkills();
    
public:
    SkillTree();
    
    void initialize();
    bool canUnlockSkill(SkillID skillId) const;
    bool unlockSkill(SkillID skillId);
    bool isSkillUnlocked(SkillID skillId) const;

    const SkillNode* getSkill(SkillID skillId) const;
    const std::unordered_set<SkillID>& getUnlockedSkills() const { return unlockedSkills; }
    
    void addSkillPoints(int points) { availablePoints += points; }
    int getAvailablePoints() const { return availablePoints; }
    
    void reset();
    
    // Get skills by branch (for UI)
    std::vector<SkillID> getSkillsByBranch(SkillBranch branch) const;
    
    // Aggregate bonuses
    int getTotalDamageDiceBonus() const;
    int getTotalFlatDamageBonus() const;
    int getTotalACBonus() const;
    int getTotalHPBonus() const;
    int getTotalSpeedBonus() const;
    float getTotalAttackSpeedBonus() const;
    float getTotalCooldownReduction() const;    
    int getTotalStrBonus() const;
    int getTotalDexBonus() const;
    int getTotalConBonus() const;
    int getTotalIntBonus() const;
    int getTotalWisBonus() const;
    int getTotalChaBonus() const;
};