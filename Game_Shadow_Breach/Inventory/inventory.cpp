#include "../Inventory/inventory.h"
#include <stdexcept>

Inventory::Inventory(float max_weight)
    : max_weight(max_weight) {
    if (max_weight <= 0) {
        throw std::invalid_argument("�������� ������������� ���� ������ ���� �������������");
    }
}

bool Inventory::add_item(Loot* item) {
    if (item == nullptr) {
        throw std::invalid_argument("������� �� ����� ���� �������");
    }

    if (total_weight + item->get_weight() > max_weight) {
        return false;
    }

    items.push_back(item);
    total_weight += item->get_weight();

    if (items.size() == 1) {
        current_item = item;
    }

    return true;
}

void Inventory::drop_current_item() {
    if (current_item == nullptr) {
        throw std::runtime_error("��� �������� ��������, ������� ����� ���� �� �������");
    }

    // ... ��������� ����������
}

void Inventory::equip_current_item() {
    if (current_item == nullptr) {
        throw std::runtime_error("��� �������� �������� ��� ���������");
    }
    equipped_item = current_item;
}

void Inventory::set_current_item(size_t index) {
    if (index >= items.size()) {
        throw std::out_of_range("����� ��������� ��� ���������");
    }
    current_item = items[index];
}

Loot* Inventory::get_equipped_item() const {
    return equipped_item;
}

Loot* Inventory::get_current_item() const {
    return current_item;
}

float Inventory::get_total_weight() const {
    return total_weight;
}

float Inventory::get_max_weight() const {
    return max_weight;
}

const TVector<Loot*>& Inventory::get_items() const {
    return items;
}