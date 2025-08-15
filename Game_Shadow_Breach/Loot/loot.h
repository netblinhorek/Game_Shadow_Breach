#pragma once
#include "C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Map_Object\\map_object.h"
class Loot : public Map_Object {
protected:
    float weight;     
public:
    virtual void OnPickup() = 0; 
};