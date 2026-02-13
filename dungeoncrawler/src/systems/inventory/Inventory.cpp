#include "Inventory.h"
#include <iostream>

Inventory::Inventory(int maxSlots) : maxSlots(maxSlots) {
}

Inventory::~Inventory() {
    items.clear();
}

bool Inventory::addItem(std::shared_ptr<Item> item) {
    if (items.size() >= (size_t)maxSlots) {
        std::cout << "Inventario lleno!" << std::endl;
        return false;
    }
    
    items.push_back(item);
    std::cout << "Añadido: " << item->getName() << std::endl;
    return true;
}

bool Inventory::removeItem(int index) {
    if (index < 0 || index >= (int)items.size()) {
        return false;
    }
    
    items.erase(items.begin() + index);
    return true;
}

Item* Inventory::getItem(int index) const {
    if (index < 0 || index >= (int)items.size()) {
        return nullptr;
    }
    return items[index].get();
}

int Inventory::getItemCount() const {
    return items.size();
}

int Inventory::getMaxSlots() const {
    return maxSlots;
}

Potion* Inventory::findFirstPotion(PotionType type) const {
    for (const auto& item : items) {
        // Intentar hacer cast a Potion
        Potion* potion = dynamic_cast<Potion*>(item.get());
        if (potion && potion->getPotionType() == type) {
            return potion;
        }
    }
    return nullptr;
}

int Inventory::findFirstPotionIndex(PotionType type) const {
    for (int i = 0; i < (int)items.size(); i++) {
        Potion* potion = dynamic_cast<Potion*>(items[i].get());
        if (potion && potion->getPotionType() == type) {
            return i;
        }
    }
    return -1;
}

void Inventory::printInventory() const {
    std::cout << "=== INVENTARIO ===" << std::endl;
    for (int i = 0; i < (int)items.size(); i++) {
        std::cout << i << ": " << items[i]->getName() 
                  << " (" << items[i]->getType() << ")" << std::endl;
    }
    std::cout << "Slots: " << items.size() << "/" << maxSlots << std::endl;
}