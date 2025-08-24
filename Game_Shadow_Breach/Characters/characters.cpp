// Character.cpp
#include "../Characters/characters.h"
#include <stdexcept>

void Character::take_damage(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("значение суммы ущерба не может быть отрицательной");
    }

    int actual_damage = amount - armor;
    if (actual_damage > 0) {
        health -= actual_damage;
        if (health < 0) health = 0;
    }
}

void Character::pick_up_item(Loot* item) {
    if (item == nullptr) {
        throw std::invalid_argument("элемент не может быть нулевым");
    }
    inventory.add_item(item);
}

void Character::drop_current_item() {
    if (inventory.get_items().size() == 0) {
        throw std::runtime_error("невозможно удалить товар - инвентарь пуст");
    }
    inventory.drop_current_item();
}