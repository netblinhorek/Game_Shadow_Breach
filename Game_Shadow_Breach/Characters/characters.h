#pragma once
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Loot\\loot.h"
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\TVector\\tvector.h"
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Map_Object\\map_object.h"
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Inventory\\inventory.h"

class Character : public Map_Object {
protected:
    int health;
    int armor;
    float speed;
    std::string name;
    int damage_bonus;
    int level;
    Inventory inventory;

public:
    Character(int x, int y, float health, float character_speed,
        const std::string& character_name, int armor = 0,
        const std::string& object_type = "Character",
        const std::string& id = "char_default",
        float max_inventory_weight = 100.0f)
        : Map_Object(x, y, character_speed, object_type, id),
        health(health),
        armor(armor),
        speed(character_speed),
        name(character_name),
        damage_bonus(0),
        level(1),
        inventory(max_inventory_weight)
    {}

    virtual void attack(Character* target) = 0;
    virtual void take_damage(int amount);

    void pick_up_item(Loot* item);
    void drop_current_item();

    int get_health() const { return health; }
    int get_armor() const { return armor; }
    float get_speed() const { return speed; }
    std::string get_name() const { return name; }
    int get_damage_bonus() const { return damage_bonus; }
    int get_level() const { return level; }
    const Inventory& get_inventory() const { return inventory; }

    void set_health(int new_health) { health = new_health; }
    void set_armor(int new_armor) { armor = new_armor; }
    void set_damage_bonus(int bonus) { damage_bonus = bonus; }
    void set_level(int new_level) { level = new_level; }
};