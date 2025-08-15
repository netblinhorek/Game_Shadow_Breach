#pragma once
#include "loot.h"
#include "tvector.h"

class Inventory {
private:
    TVector<Loot*> items;         
    Loot* equippedItem = nullptr; 
    Loot* currentItem = nullptr;   
    float totalWeight = 0.0f;      
    float maxWeight;               

public:
    explicit Inventory(float maxWeight);
    bool AddItem(Loot* item);
    void DropCurrentItem();
    void EquipCurrentItem();
    void SetCurrentItem(size_t index);

    
    Loot* GetEquippedItem() const;
    Loot* GetCurrentItem() const;
    float GetTotalWeight() const;
    float GetMaxWeight() const;
    const TVector<Loot*>& GetItems() const;
};