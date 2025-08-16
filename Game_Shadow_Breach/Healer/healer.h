#pragma once
#include "characters.h"
class Healer : public Character {
private:
    int holyEnergy;         

public:
    void Heal(Character* target);   
    void Resurrect(Character* target);  
    void Attack(Character* target) override;
};