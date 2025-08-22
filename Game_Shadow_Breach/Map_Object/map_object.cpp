// Map_Object.cpp
#include "map_object.h"
#include <stdexcept>

Map_Object::Map_Object(int x, int y, float speed, std::string object_type, std::string id)
    : x(x), y(y), speed(speed), object_type(std::move(object_type)), id(std::move(id))
{
    if (!validate_coordinates(x, y)) {
        throw std::invalid_argument("неверные координаты");
    }
    if (speed < 0) {
        throw std::invalid_argument("значение скорости не может быть отрицательной");
    }
    if (object_type.empty()) {
        throw std::invalid_argument("тип объекта не может быть пустым");
    }
    if (id.empty()) {
        throw std::invalid_argument("номер id не может быть пустым");
    }
}

bool Map_Object::validate_coordinates(int x, int y) const {
    return true;
}

void Map_Object::move(Direction dir) {
    switch (dir) {
    case Direction::Up: y--; break;
    case Direction::Down: y++; break;
    case Direction::Left: x--; break;
    case Direction::Right: x++; break;
    }
}

void Map_Object::teleport(int new_x, int new_y) {
    if (!validate_coordinates(new_x, new_y)) {
        throw std::invalid_argument("неверные координаты для телепорта");
    }
    x = new_x;
    y = new_y;
}

std::pair<int, int> Map_Object::get_coordinates() const {
    return { x, y };
}

const std::string& Map_Object::get_id() const {
    return id;
}

float Map_Object::get_speed() const {
    return speed;
}

const std::string& Map_Object::get_object_type() const {
    return object_type;
}