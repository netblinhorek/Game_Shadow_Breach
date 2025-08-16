#pragma once
#include "map_object.h"
class Key : public Map_Object {
private:
    int doorId; 
    bool isOpen; 
public:
    Key(int id, float x, float y, int doorId);
    void open(); 
    bool getIsOpen() const;
};