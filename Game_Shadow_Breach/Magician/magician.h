#pragma once
#include "characters.h"
#include "potion.h"
#include "tvector.h"
class Magicial : public Character {
private:
    int mana;                   
    TVector <Potion*> potion;     

public:
    void CastSpell(Potion* spell);  
    void Attack(Character* target) override;
};