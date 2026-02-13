// Item.cpp
#include "Item.h"

Item::Item(const std::string& name, const std::string& desc, float weight, int value)
    : name(name), description(desc), weight(weight), value(value), isEquipped(false) {
}

// Getters
std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

float Item::getWeight() const {
    return weight;
}

int Item::getValue() const {
    return value;
}

bool Item::getIsEquipped() const {
    return isEquipped;
}

// Setters
void Item::setIsEquipped(bool equipped) {
    isEquipped = equipped;
}