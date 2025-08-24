#pragma once
#include "../Loot/loot.h"
#include <string>

class Armor : public Loot {
private:
    int defense;
    int durability;
public:
    Armor(float weight, int x, int y, const std::string& id,
        int defense, int durability);
    int get_defense() const;
    void reduce_durability(int amount);
    bool is_broken() const;
    void repair();
};