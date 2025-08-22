#include "healer.h"
#include <stdexcept>

Healer::Healer(int x, int y, float health, float speed,
    const std::string& name, int armor, int holy_energy)
    : Character(x, y, health, speed, name, armor), holy_energy(holy_energy)
{
    if (holy_energy < 0) {
        throw std::invalid_argument("������ ������� �� ����� ���� ����������");
    }
}

void Healer::heal(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("���� �� ����� ���� �������");
    }

    if (holy_energy >= 10) {
        target->take_damage(-25); 
        holy_energy -= 10;
    }
    else {
        throw std::runtime_error("������������ ������ ������� ��� ���������");
    }
}

void Healer::resurrect(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("���� �� ����� ���� �������");
    }

    if (holy_energy >= 30) {
        holy_energy -= 30;
    }
    else {
        throw std::runtime_error("������������ ������ ������� ��� �����������");
    }
}

void Healer::attack(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("���� �� ����� ���� �������");
    }

    int base_damage = 8;
    int bonus_damage = holy_energy / 5;

    target->take_damage(base_damage + bonus_damage);

    holy_energy += 2;

    if (holy_energy > 100) {
        holy_energy = 100;
    }
}