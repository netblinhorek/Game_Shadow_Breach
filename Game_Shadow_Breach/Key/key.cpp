#include "key.h"
#include <stdexcept>

Key::Key(int id, float x, float y, int door_id)
    : Map_Object(static_cast<int>(x), static_cast<int>(y), 0.0f, "Key", "key_" + std::to_string(id)),
    door_id(door_id),
    is_open_status(false)  
{
    if (id <= 0) {
        throw std::invalid_argument("номер ключа должен быть положительным");
    }
    if (door_id <= 0) {
        throw std::invalid_argument("номер двери должен быть положительным");
    }
}

void Key::open() {
    if (is_open_status) {  
        throw std::runtime_error("ключ уже открыт");
    }
    is_open_status = true;  
}

bool Key::is_open() const {
    return is_open_status;
}