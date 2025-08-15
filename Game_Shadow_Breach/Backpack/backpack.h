#pragma once
#include "loot.h"
#include "tvector.h"
class Backpack {
private:
    TVector<Loot*> inventory;
    Loot* handItem; 
    Loot* currentItem; 
    int totalWeight; 
    int maxWeight; 
public:
    Backpack(int maxWeight);
    void addItem(Loot* item); 
    void dropCurrentItem(); 
    void takeCurrentItemInHand(); 
    bool isFull() const;
};