#pragma once
#include "../Map_Object/map_object.h"

class Key : public Map_Object {
private:
    int door_id;
    bool is_open_status;  

public:
    Key(int id, float x, float y, int door_id);
    void open();
    bool is_open() const;

    int get_door_id() const { return door_id; }
    void reset() { is_open_status = false; }
};