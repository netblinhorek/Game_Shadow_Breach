#pragma once
#include "loot.h"
#include <string>
class Armor : public Loot {
private:
    int defense; 
    int durability; 
public:
    Armor(int id, const std::string& name, int quantity, 
        int weight, int defense, int durability);
    int getDefense() const;
    void reduceDurability(int amount);
};