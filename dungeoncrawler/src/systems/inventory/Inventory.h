#pragma once

#include "../../Items/Item.h"
#include "../../Items/Potion.h"
#include <vector>
#include <memory>

class Inventory {
private:
    std::vector<std::shared_ptr<Item>> items;
    int maxSlots;

public:
    Inventory(int maxSlots = 20);
    ~Inventory();

    bool addItem(std::shared_ptr<Item> item);
    bool removeItem(int index);
    Item* getItem(int index) const;
    
    int getItemCount() const;
    int getMaxSlots() const;
    
    // Método útil para encontrar primera poción de un tipo
    Potion* findFirstPotion(PotionType type) const;
    int findFirstPotionIndex(PotionType type) const;
    
    void printInventory() const; // debug
};