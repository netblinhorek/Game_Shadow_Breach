#pragma once
#include "characters.h"
#include "tvector.h"
class Warrior : public Character {
private:
    int rage;        
    bool berserkMode;   
    TVector <Buff> buffs; //??? когда инет появ, глянуть табл

public:
    void ShieldBash(); 
    void Attack(Character* target) override;
};