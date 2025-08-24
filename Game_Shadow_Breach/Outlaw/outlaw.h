#pragma once
#include "../Characters/characters.h"

class Outlaw : public Character {
private:
    int stealth;
    float crit_chance;

public:
    // Конструктор должен соответствовать реализации
    Outlaw(int id, int x, int y, float speed,
        int health, int armor, int level,
        int stealth, float crit_chance);

    void backstab(Character& target);
    void sneak();

    int get_stealth() const { return stealth; }
    float get_crit_chance() const { return crit_chance; }

    void set_stealth(int new_stealth);
    void set_crit_chance(float new_chance);
};