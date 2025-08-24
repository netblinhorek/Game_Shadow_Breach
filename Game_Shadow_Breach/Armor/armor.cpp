#include "../Armor/armor.h"
#include <stdexcept>

Armor::Armor(float weight, int x, int y, const std::string& id,
    int defense, int durability)
    : Loot(weight, x, y, id),
    defense(defense),
    durability(durability)
{
    if (defense <= 0) {
        throw std::invalid_argument("�������� ������ ������ ���� ����������");
    }
    if (durability <= 0) {
        throw std::invalid_argument("�������� ������������� ������ ���� �������������");
    }
    if (weight <= 0) {
        throw std::invalid_argument("�������� ���� ������ ���� �������������");
    }
}

int Armor::get_defense() const {
    return defense;
}

void Armor::reduce_durability(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("�������� ����� ������ ���� �������������");
    }
    durability -= amount;
    if (durability < 0) {
        durability = 0;
    }
}

bool Armor::is_broken() const {
    return durability <= 0;
}

void Armor::repair() {
   durability = 100; 
}