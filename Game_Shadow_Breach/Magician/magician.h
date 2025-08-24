#pragma once
#include "../Characters/characters.h"
#include "../Potion/potion.h"
#include "../TVector/tvector.h"

class Magician : public Character {
private:
    int mana;
    TVector<Potion*> potions;

public:
    Magician(int x, int y, float health, float speed,
        const std::string& name, int armor = 0, int mana = 100);

    void cast_spell(Potion* spell);
    void attack(Character* target) override;

    int get_mana() const { return mana; }

    void set_mana(int new_mana);
    const TVector<Potion*>& get_potions() const;
};