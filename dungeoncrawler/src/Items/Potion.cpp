// Potion.cpp
#include "Potion.h"
#include <iostream>

Potion::Potion(const std::string& name, const std::string& desc, float weight, 
               int value, PotionType type, int power, int duration)
    : Item(name, desc, weight, value), potionType(type), 
      effectPower(power), duration(duration) {
}

// Getters
PotionType Potion::getPotionType() const {
    return potionType;
}

int Potion::getEffectPower() const {
    return effectPower;
}

int Potion::getDuration() const {
    return duration;
}

// Override métodos virtuales
void Potion::use() {
    std::cout << "Usando poción: " << name << std::endl;
    
    switch(potionType) {
        case PotionType::HEALING:
            std::cout << "Curas " << effectPower << " puntos de vida." << std::endl;
            // Aquí llamarías a character->heal(effectPower);
            break;
        case PotionType::MANA:
            std::cout << "Recuperas " << effectPower << " puntos de maná." << std::endl;
            break;
        case PotionType::STRENGTH:
            std::cout << "Ganas +" << effectPower << " de fuerza durante " 
                      << duration << " turnos." << std::endl;
            break;
        // ... otros casos
        default:
            std::cout << "Efecto de poción desconocido." << std::endl;
    }
}

std::string Potion::getType() const {
    return "Potion";
}