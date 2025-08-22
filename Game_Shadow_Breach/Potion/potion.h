#pragma once
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Loot\\loot.h"
#include <string>
#include "characters.h"

class Potion : public Loot {
private:
    std::string potion_name;
    int healing_amount;
    int defense_bonus;
    int uses_remaining;
    int max_uses;
    bool is_key;
    int door_id;
    int mana_cost;           
    int spell_damage;        

public:
    
    Potion(float weight, int x, int y, const std::string& id,
           const std::string& name, int healing, int defense, int uses,
           int mana_cost = 0, int spell_damage = 0);
    Potion(float weight, int x, int y, const std::string& id,
           const std::string& name, int door_id);

    void on_pickup() override;

    
    void use_healing();
    void use_defense();
    bool use_as_key();
    void apply_effect(Character* target); 

    std::string get_potion_name() const { return potion_name; }
    int get_healing_amount() const { return healing_amount; }
    int get_defense_bonus() const { return defense_bonus; }
    int get_uses_remaining() const { return uses_remaining; }
    int get_max_uses() const { return max_uses; }
    bool get_is_key() const { return is_key; }
    int get_door_id() const { return door_id; }
    int get_mana_cost() const { return mana_cost; }        
    int get_spell_damage() const { return spell_damage; }  

    bool is_empty() const { return uses_remaining <= 0; }
    bool can_use() const { return uses_remaining > 0; }

    void refill(int amount);
};