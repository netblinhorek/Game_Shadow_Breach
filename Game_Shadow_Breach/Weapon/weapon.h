#pragma once
#include "../Loot/loot.h"
#include <string>

class Weapon : public Loot {
private:
    int damage;
    std::string weapon_name;

public:
    Weapon(float weight, int x, int y, const std::string& id,
        const std::string& name, int damage);

    int get_damage() const;
    std::string get_name() const { return weapon_name; }

    void upgrade(int bonus_damage);
    bool is_broken() const; 
};