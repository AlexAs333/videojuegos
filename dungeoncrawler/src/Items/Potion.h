// Potion.h
#ifndef POTION_H
#define POTION_H

#include "Item.h"

enum class PotionType {
    HEALING,
    MANA,
    STRENGTH,
    DEXTERITY,
    CONSTITUTION,
    INTELLIGENCE,
    WISDOM,
    CHARISMA,
    POISON,
    ANTIDOTE,
    INVISIBILITY,
    SPEED
};

class Potion : public Item {
private:
    PotionType potionType;
    int effectPower; // poder del efecto (ej: cuánto cura)
    int duration; // duración en turnos (0 si es instantáneo)

public:
    Potion(const std::string& name, const std::string& desc, float weight, 
           int value, PotionType type, int power, int duration);

    // Getters
    PotionType getPotionType() const;
    int getEffectPower() const;
    int getDuration() const;

    // Override métodos virtuales
    void use() override;
    std::string getType() const override;
};

#endif