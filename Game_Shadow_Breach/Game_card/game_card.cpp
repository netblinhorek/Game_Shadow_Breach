#include "game_card.h"
#include <stdexcept>
#include <random>

GameMap::GameMap() {
}

void GameMap::place_object(Map_Object* obj) {
    if (obj == nullptr) {
        throw std::invalid_argument("невозможно разместить нулевой объект на карте");
    }
    map_objects.push_back(obj);
}

void GameMap::place_object_at(Map_Object* obj, float x, float y) {
    if (obj == nullptr) {
        throw std::invalid_argument("невозможно разместить нулевой объект на карте");
    }

    obj->teleport(static_cast<int>(x), static_cast<int>(y));
    map_objects.push_back(obj);
}

Map_Object* GameMap::get_object_at(float x, float y) {
    int target_x = static_cast<int>(x);
    int target_y = static_cast<int>(y);

    for (size_t i = 0; i < map_objects.size(); ++i) {
        auto obj = map_objects.at(i);
        auto coords = obj->get_coordinates();
        if (coords.first == target_x && coords.second == target_y) {
            return obj;
        }
    }
    return nullptr;
}

bool GameMap::is_game_object_at(float x, float y) {
    return get_object_at(x, y) != nullptr;
}

void GameMap::generate_random_start_map(const TVector<Character*>& characters, const TVector<Loot*>& items) {
    map_objects.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 49);

    for (size_t i = 0; i < characters.size(); ++i) {
        Character* character = const_cast<Character*>(characters.data()[i]);
        int x, y;
        do {
            x = dist(gen);
            y = dist(gen);
        } while (is_game_object_at(x, y));

        character->teleport(x, y);
        map_objects.push_back(character);
    }

    for (size_t i = 0; i < items.size(); ++i) {
        Loot* item = const_cast<Loot*>(items.data()[i]);
        int x, y;
        do {
            x = dist(gen);
            y = dist(gen);
        } while (is_game_object_at(x, y));

        item->teleport(x, y);
        map_objects.push_back(item);
    }
}