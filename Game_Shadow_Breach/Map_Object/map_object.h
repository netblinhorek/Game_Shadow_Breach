#pragma once
#include <utility>
#include <string>
#include <stdexcept>

class Map_Object {
protected:
    int x, y;
    float speed;
    std::string object_type;
    std::string id;

    virtual bool validate_coordinates(int x, int y) const;

public:
    enum class Direction { Up, Down, Left, Right };

    Map_Object(int x, int y, float speed, std::string object_type, std::string id);
    virtual ~Map_Object() = default;

    virtual void move(Direction dir);
    virtual void teleport(int new_x, int new_y);

    std::pair<int, int> get_coordinates() const;
    const std::string& get_id() const;
    float get_speed() const;
    const std::string& get_object_type() const;
};