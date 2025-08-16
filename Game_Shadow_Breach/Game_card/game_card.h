#pragma once
#include "map_object.h"
#include "characters.h"
#include "loot.h"
#include "tvector.h"
class GameMap {
private:
    TVector<Map_Object*> mapObjects;
public:
    GameMap();
    void placeObject(Map_Object* obj);
    void placeObjectAt(Map_Object* obj, float x, float y);
    Map_Object* getObjectAt(float x, float y);
    bool isGameObjectAt(float x, float y);
    void generateRandomStartMap(const TVector <Character*>& characters, const TVector <Loot*>& items);
};