#include "../Magician/magician.h"
#include <stdexcept>

Magician::Magician(int x, int y, float health, float speed,
    const std::string& name, int armor, int mana)
    : Character(x, y, health, speed, name, armor), mana(mana)
{
    if (mana < 0) {
        throw std::invalid_argument("значение маны не может быть отрицательной");
    }
}

void Magician::cast_spell(Potion* spell) {
    if (spell == nullptr) {
        throw std::invalid_argument("значение заклинания не может быть нулевым");
    }

    if (mana >= spell->get_mana_cost()) {
        spell->apply_effect(this);
        mana -= spell->get_mana_cost();
        potions.push_back(spell);
    }
    else {
        throw std::runtime_error("недостаточно маны для произнесения заклинания");
    }
}

void Magician::attack(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("значение цели не может быть нулевой");
    }

    int base_damage = 12;
    int mana_bonus = mana / 10;
    target->take_damage(base_damage + mana_bonus);

    mana += 5;
    if (mana > 200) {
        mana = 200;
    }

    for (size_t i = 0; i < potions.size(); ++i) {
        if (potions[i]->get_spell_damage() > 0) {
            target->take_damage(potions[i]->get_spell_damage());
        }
    }
}

void Magician::set_mana(int new_mana) {
    if (new_mana < 0) {
        throw std::invalid_argument("значение маны не может быть отрицательной");
    }
    mana = new_mana;
    if (mana > 200) {
        mana = 200;
    }
}

const TVector<Potion*>& Magician::get_potions() const {
    return potions;
}