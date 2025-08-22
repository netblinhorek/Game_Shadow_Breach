#pragma once
#include "characters.h"

class Healer : public Character {
private:
    int holy_energy;

public:
    Healer(int x, int y, float health, float speed,
        const std::string& name, int armor = 0, int holy_energy = 50);

    void heal(Character* target);
    void resurrect(Character* target);
    void attack(Character* target) override;

    int get_holy_energy() const { return holy_energy; }
    void set_holy_energy(int energy) { holy_energy = energy; }
};