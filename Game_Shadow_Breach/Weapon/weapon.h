#pragma once
#include "loot.h"
#include <string>
class Weapon : public Loot {
private:
    int damage; 
public:
    Weapon(int id, const std::string& name,
        int quantity, int weight, int damage);
    int getDamage() const;
};