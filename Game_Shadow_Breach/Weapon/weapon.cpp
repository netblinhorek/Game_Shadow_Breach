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
        throw std::invalid_argument("����� ������ ���� �������������");
    }
    if (weight <= 0) {
        throw std::invalid_argument("��� ������ ���� �������������");
    }
    if (name.empty()) {
        throw std::invalid_argument("�������� ������ �� ����� ���� ������");
    }
}

int Weapon::get_damage() const {
    return damage;
}

void Weapon::upgrade(int bonus_damage) {
    if (bonus_damage <= 0) {
        throw std::invalid_argument("�������������� ���� ������ ���� �������������");
    }
    damage += bonus_damage;
}

bool Weapon::is_broken() const {
    return damage < 5;
}