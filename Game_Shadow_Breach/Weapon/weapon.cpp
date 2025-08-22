// Weapon.cpp
#include "weapon.h"
#include <stdexcept>

Weapon::Weapon(float weight, int x, int y, const std::string& id,
    const std::string& name, int damage)
    : Loot(weight, x, y, id),
    damage(damage),
    weapon_name(name)
{
    if (damage <= 0) {
        throw std::invalid_argument("ущерб должен быть положительным");
    }
    if (weight <= 0) {
        throw std::invalid_argument("вес должен быть положительным");
    }
    if (name.empty()) {
        throw std::invalid_argument("название оружия не может быть пустым");
    }
}

int Weapon::get_damage() const {
    return damage;
}

void Weapon::upgrade(int bonus_damage) {
    if (bonus_damage <= 0) {
        throw std::invalid_argument("дополнительный урон должен быть положительным");
    }
    damage += bonus_damage;
}

bool Weapon::is_broken() const {
    return damage < 5;
}