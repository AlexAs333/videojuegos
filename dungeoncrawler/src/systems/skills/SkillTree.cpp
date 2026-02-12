#include  "SkillTree.h"

SkillData::SkillData()
    : id(SkillID::NONE), branch(SkillBranch::COMMON), 
      damageDiceBonus(0), damageDiceType(6), flatDamageBonus(0),
      acBonus(0), hpBonus(0), speedBonus(0), attackSpeedBonus(0.0f), 
      cooldown(0.0f), cooldownReduction(0.0f),
      strBonus(0), dexBonus(0), conBonus(0), intBonus(0), wisBonus(0), chaBonus(0),
      scalingStat(""), fireSpellBonus(0.0f), windSpellBonus(0.0f), natureSpellBonus(0.0f),
      damageType(DamageType::NONE), isPassive(true), grantsAbility(false), abilityName("") {}

SkillNode::SkillNode(const SkillData& skillData, const std::vector<SkillID>& prereqs)
    : data(skillData), prerequisites(prereqs), unlocked(false) {}

SkillTree::SkillTree() : availablePoints(0) {}

void SkillTree::initialize() {
    skills.clear();
    unlockedSkills.clear();
    initializeSkills();
}

void SkillTree::initializeSkills() {
    initializeCommonSkills();
    initializeMageSkills();
    initializeWarriorSkills();
    initializeRogueSkills();
    initializeMulticlassSkills();
}

void SkillTree::initializeCommonSkills() {
    // Cooldown Reduction
    SkillData cooldownReduction;
    cooldownReduction.id = SkillID::COOLDOWN_REDUCTION;
    cooldownReduction.name = "Cooldown Reduction";
    cooldownReduction.description = "Reduce el cooldown de todas tus habilidades en un 10%.";
    cooldownReduction.branch = SkillBranch::COMMON;
    cooldownReduction.cooldownReduction = 0.1f; // Reduce cooldown by 10%
    cooldownReduction.isPassive = true;
    skills[SkillID::COOLDOWN_REDUCTION] = std::make_unique<SkillNode>(cooldownReduction);
}

void SkillTree::initializeMageSkills() {
    /* ============= MAGE BRANCH - Common ============= */
    // Eldritch Blast
    SkillData eldritchBlast;
    eldritchBlast.id = SkillID::MAGE_ELDRITCH_BLAST;
    eldritchBlast.name = "Eldritch Blast";
    eldritchBlast.description = "Un ataque a distancia que inflige 1d10 de daño de fuerza. Se le suma la inteligencia como modificador de daño.";
    eldritchBlast.branch = SkillBranch::MAGE_COMMON;
    eldritchBlast.damageDiceBonus = 1; // 1 extra die
    eldritchBlast.damageDiceType = 10; // d10   
    eldritchBlast.scalingStat = "INT"; // Scales with Intelligence
    eldritchBlast.isPassive = false;
    eldritchBlast.damageType = DamageType::FORCE;
    skills[SkillID::MAGE_ELDRITCH_BLAST] = std::make_unique<SkillNode>(eldritchBlast);

    // Eldritch Blast II
    SkillData eldritchBlastII = eldritchBlast;
    eldritchBlastII.id = SkillID::MAGE_ELDRITCH_BLAST_II;
    eldritchBlastII.name = "Eldritch Blast II"; 
    eldritchBlastII.description = "Tu Eldritch Blast ahora inflige 2d10 de daño de fuerza.";
    eldritchBlastII.damageDiceBonus = 2; // 2 extra dice
    skills[SkillID::MAGE_ELDRITCH_BLAST_II] = std::make_unique<SkillNode>(eldritchBlastII, std::vector<SkillID>{SkillID::MAGE_ELDRITCH_BLAST});

    // Eldritch Blast III
    SkillData eldritchBlastIII = eldritchBlastII;
    eldritchBlastIII.id = SkillID::MAGE_ELDRITCH_BLAST_III;
    eldritchBlastIII.name = "Eldritch Blast III";
    eldritchBlastIII.description = "Tu Eldritch Blast ahora inflige 3d10 de daño de fuerza.";
    eldritchBlastIII.damageDiceBonus = 3; // 3 extra dice
    skills[SkillID::MAGE_ELDRITCH_BLAST_III] = std::make_unique<SkillNode>(eldritchBlastIII, std::vector<SkillID>{SkillID::MAGE_ELDRITCH_BLAST_II});

    // Eldritch Blast IV
    SkillData eldritchBlastIV = eldritchBlastIII;
    eldritchBlastIV.id = SkillID::MAGE_ELDRITCH_BLAST_IV;
    eldritchBlastIV.name = "Eldritch Blast IV";
    eldritchBlastIV.description = "Tu Eldritch Blast ahora inflige 4d10 de daño de fuerza.";
    eldritchBlastIV.damageDiceBonus = 4; // 4 extra dice    
    skills[SkillID::MAGE_ELDRITCH_BLAST_IV] = std::make_unique<SkillNode>(eldritchBlastIV, std::vector<SkillID>{SkillID::MAGE_ELDRITCH_BLAST_III});

    // Intelligence Boost
    SkillData intelligenceBoost;
    intelligenceBoost.id = SkillID::MAGE_INTELLIGENCE_BOOST;
    intelligenceBoost.name = "Intelligence Boost";
    intelligenceBoost.description = "Aumenta tu inteligencia en 1 punto";
    intelligenceBoost.branch = SkillBranch::MAGE_COMMON;
    intelligenceBoost.intBonus = 1; // +1 Intelligence
    intelligenceBoost.isPassive = true;
    skills[SkillID::MAGE_INTELLIGENCE_BOOST] = std::make_unique<SkillNode>(intelligenceBoost);

    /* ============= FIRE BRANCH ============= */
    // Firebolt
    SkillData firebolt;
    firebolt.id = SkillID::MAGE_FIREBOLT;   
    firebolt.name = "Firebolt";
    firebolt.description = "Un ataque a distancia que inflige 1d10 de daño de fuego. Se le suma la inteligencia como modificador de daño.";
    firebolt.branch = SkillBranch::MAGE_FIRE;   
    firebolt.damageDiceBonus = 1; // 1 extra die
    firebolt.damageDiceType = 10; // d10
    firebolt.scalingStat = "INT"; // Scales with Intelligence
    firebolt.damageType = DamageType::FIRE;
    skills[SkillID::MAGE_FIREBOLT] = std::make_unique<SkillNode>(firebolt);

    // Firebolt II
    SkillData fireboltII = firebolt;
    fireboltII.id = SkillID::MAGE_FIREBOLT_II;
    fireboltII.name = "Firebolt II";
    fireboltII.description = "Tu Firebolt ahora inflige 2d10 de daño de fuego.";
    fireboltII.damageDiceBonus = 2; // 2 extra dice
    skills[SkillID::MAGE_FIREBOLT_II] = std::make_unique<SkillNode>(fireboltII, std::vector<SkillID>{SkillID::MAGE_FIREBOLT});

    // Fire Resistance
    SkillData fireResistance;
    fireResistance.id = SkillID::MAGE_FIRE_RESISTANCE;
    fireResistance.name = "Fire Resistance";
    fireResistance.description = "Obtienes resistencia al daño de fuego (daño de fuego se reduce a la mitad).";
    fireResistance.branch = SkillBranch::MAGE_FIRE;
    fireResistance.isPassive = true;
    skills[SkillID::MAGE_FIRE_RESISTANCE] = std::make_unique<SkillNode>(fireResistance, std::vector<SkillID>{SkillID::MAGE_FIREBOLT});

    // Fireball
    SkillData fireball;
    fireball.id = SkillID::MAGE_FIREBALL;
    fireball.name = "Fireball";
    fireball.description = "Lanzas una bola de fuego que explota al impactar, infligiendo 8d6 de daño de fuego en un área. Se le suma la inteligencia como modificador de daño.";
    fireball.branch = SkillBranch::MAGE_FIRE;
    fireball.damageDiceBonus = 8; // 8 extra dice
    fireball.damageDiceType = 6; // d6
    fireball.scalingStat = "INT"; // Scales with Intelligence
    fireball.damageType = DamageType::FIRE;
    skills[SkillID::MAGE_FIREBALL] = std::make_unique<SkillNode>(fireball, std::vector<SkillID>{SkillID::MAGE_FIREBOLT_II, SkillID::MAGE_FIRE_RESISTANCE});

    // Fire Spells Boost
    SkillData fireSpellsBoost;
    fireSpellsBoost.id = SkillID::MAGE_FIRE_SPELLS_BOOST;
    fireSpellsBoost.name = "Fire Spells Boost";
    fireSpellsBoost.description = "Aumenta el daño de tus hechizos de fuego en un 20%.";
    fireSpellsBoost.branch = SkillBranch::MAGE_FIRE;
    fireSpellsBoost.fireSpellBonus = 0.2f; // Increase fire spell damage by 20%
    fireSpellsBoost.isPassive = true;
    fireSpellsBoost.damageType = DamageType::FIRE;
    skills[SkillID::MAGE_FIRE_SPELLS_BOOST] = std::make_unique<SkillNode>(fireSpellsBoost, std::vector<SkillID>{SkillID::MAGE_FIREBALL});

    // Nova
    SkillData nova;
    nova.id = SkillID::MAGE_NOVA;   
    nova.name = "Nova";
    nova.description = "Una explosión de energía mágica de fuego que inflige 10d8 de daño de fuego a todos los enemigos cercanos. Se le suma la inteligencia como modificador de daño.";
    nova.branch = SkillBranch::MAGE_FIRE;
    nova.damageDiceBonus = 10; // 10 extra dice
    nova.damageDiceType = 8; // d8
    nova.scalingStat = "INT"; // Scales with Intelligence
    nova.isPassive = false; 
    nova.damageType = DamageType::FIRE;
    skills[SkillID::MAGE_NOVA] = std::make_unique<SkillNode>(nova, std::vector<SkillID>{SkillID::MAGE_FIRE_SPELLS_BOOST});


