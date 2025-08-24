// Loot.cpp
#include "../Loot/loot.h"
#include <stdexcept>

Loot::Loot(float w, int x, int y, std::string id)
    : Map_Object(x, y, 0.0f, "Loot", id), weight(w)
{
    if (w <= 0) {
        throw std::invalid_argument("значение веса должен быть положительным");
    }
}