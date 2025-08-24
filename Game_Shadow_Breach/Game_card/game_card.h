#pragma once
#include "../Map_Object/map_object.h"
#include "../Characters/characters.h"
#include "../Loot/loot.h"
#include "../TVector/tvector.h"

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