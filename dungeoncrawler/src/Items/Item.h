// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
protected:
    std::string name;
    std::string description;
    float weight;               //? necesario?
    int value;
    bool isEquipped;

public:
    Item(const std::string& name, const std::string& desc, float weight, int value);
    virtual ~Item() = default;

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    float getWeight() const;
    int getValue() const;
    bool getIsEquipped() const;

    // Setters
    void setIsEquipped(bool equipped);

    // Métodos virtuales puros
    virtual void use() = 0;
    virtual std::string getType() const = 0;
};

#endif