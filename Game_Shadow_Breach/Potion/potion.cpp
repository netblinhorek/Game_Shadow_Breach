#include "potion.h"
#include <stdexcept>

Potion::Potion(float weight, int x, int y, const std::string& id,
    const std::string& name, int healing, int defense, int uses,
    int mana_cost, int spell_damage)
    : Loot(weight, x, y, id),
    potion_name(name),
    healing_amount(healing),
    defense_bonus(defense),
    uses_remaining(uses),
    max_uses(uses),
    is_key(false),
    door_id(-1),
    mana_cost(mana_cost),
    spell_damage(spell_damage)
{
    if (healing < 0) throw std::invalid_argument("��������� �� ����� ���� ����������");
    if (defense < 0) throw std::invalid_argument("������ �� ����� ���� ����������");
    if (uses <= 0) throw std::invalid_argument("������������� ������ ���� �������������");
}

Potion::Potion(float weight, int x, int y, const std::string& id,
    const std::string& name, int door_id)
    : Loot(weight, x, y, id),
    potion_name(name),
    healing_amount(0),
    defense_bonus(0),
    uses_remaining(1),
    max_uses(1),
    is_key(true),
    door_id(door_id),
    mana_cost(0),
    spell_damage(0)
{
    if (door_id <= 0) throw std::invalid_argument("������������� ����� ������ ���� �������������");
}

void Potion::on_pickup() {
    if (can_use()) {
        if (healing_amount > 0) {
            use_healing();
        }
        else if (defense_bonus > 0) {
            use_defense();
        }
        else if (is_key) {
            use_as_key();
        }
    }
}

void Potion::apply_effect(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("���� �� ����� ���� �������");
    }

    if (is_empty()) {
        throw std::runtime_error("����� ������");
    }

    if (healing_amount > 0) {
        target->take_damage(-healing_amount); 
    }

    if (defense_bonus > 0) {
       target->set_armor(target->get_armor() + defense_bonus);
    }

    if (spell_damage > 0) {
        target->take_damage(spell_damage);
    }

    uses_remaining--;
}

void Potion::use_healing() {
    if (is_empty()) {
        throw std::runtime_error("����� ������");
    }
    if (is_key) {
        throw std::runtime_error("��� ����� - ����, ��� ������ ������������ ��� ���������");
    }
    uses_remaining--;
}

void Potion::use_defense() {
    if (is_empty()) {
        throw std::runtime_error("����� ������");
    }
    if (is_key) {
        throw std::runtime_error("��� ����� �������� ������, ��� ������ ������������ ��� ������");
    }
    uses_remaining--;
}

bool Potion::use_as_key() {
    if (!is_key) {
        throw std::runtime_error("��� ����� - �� ���� � ��������");
    }
    if (is_empty()) {
        return false;
    }
    uses_remaining--;
    return true;
}

void Potion::refill(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("����� ���������� ������ ���� �������������");
    }
    if (is_key) {
        throw std::runtime_error("�������� ����� �� ����� ���� ��������� ��������");
    }
    uses_remaining += amount;
    if (uses_remaining > max_uses) {
        uses_remaining = max_uses;
    }
}