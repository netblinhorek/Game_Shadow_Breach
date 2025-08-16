#pragma once
#include "characters.h"
class Outlaw : public Character {
private:
    int stealth; 
    float critChance; 
public:
    Outlaw(int id, float x, float y, float speed, 
        int health, int armor, int level,
        int stealth, float critChance);
    void backstab(Character& target);
};