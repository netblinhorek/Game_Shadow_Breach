#pragma once
#include "loot.h"
#include "tvector.h"
#include "map_object.h"
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Inventory\\inventory.h"
class Character : public Map_Object {
protected:
    
    int health;          
    int armor;           
    int damageBonus;     
    int level;          
    Inventory inventory;
public:
    
    virtual void Attack(Character* target) = 0;  
    virtual void TakeDamage(int amount);      

    void PickUpItem(Loot* item);      
    void DropCurrentItem();         
};