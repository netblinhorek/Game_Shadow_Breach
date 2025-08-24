#pragma once
#include "../Loot/loot.h"
#include "../TVector/tvector.h"

class Inventory {
private:
    TVector<Loot*> items;
    Loot* equipped_item = nullptr;
    Loot* current_item = nullptr;
    float total_weight = 0.0f;
    float max_weight;

public:
    explicit Inventory(float max_weight);
    bool add_item(Loot* item);
    void drop_current_item();
    void equip_current_item();
    void set_current_item(size_t index);


    Loot* get_equipped_item() const;
    Loot* get_current_item() const;
    float get_total_weight() const;
    float get_max_weight() const;
    const TVector<Loot*>& get_items() const;
};