#pragma once
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Map_Object\\map_object.h"  // Используем относительный путь

class Loot : public Map_Object {
protected:
    float weight;
public:
    Loot(float w, int x, int y, std::string id);

    virtual void on_pickup() = 0;  

    float get_weight() const { return weight; }

    virtual ~Loot() = default;
};