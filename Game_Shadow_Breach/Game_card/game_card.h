#pragma once
#include "map_object.h"
#include "characters.h"
#include "loot.h"
#include "tvector.h"

class GameMap {
private:
    TVector<Map_Object*> map_objects;

public:
    GameMap();
    void place_object(Map_Object* obj);
    void place_object_at(Map_Object* obj, float x, float y);
    Map_Object* get_object_at(float x, float y);
    bool is_game_object_at(float x, float y);
    void generate_random_start_map(const TVector<Character*>& characters, const TVector<Loot*>& items);
};