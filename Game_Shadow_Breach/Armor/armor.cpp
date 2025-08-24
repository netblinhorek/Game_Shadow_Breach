#include "../Armor/armor.h"
#include <stdexcept>

Armor::Armor(float weight, int x, int y, const std::string& id,
    int defense, int durability)
    : Loot(weight, x, y, id),
    defense(defense),
    durability(durability)
{
    if (defense <= 0) {
        throw std::invalid_argument("значение защиты должна быть позитивной");
    }
    if (durability <= 0) {
        throw std::invalid_argument("значение долговечности должна быть положительной");
    }
    if (weight <= 0) {
        throw std::invalid_argument("значение веса должен быть положительным");
    }
}

int Armor::get_defense() const {
    return defense;
}

void Armor::reduce_durability(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("значение суммы должна быть положительной");
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