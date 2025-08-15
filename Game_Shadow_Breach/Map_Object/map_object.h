#pragma once
#include <utility>   
#include <string>    
#include <iostream>  


class Map_Object {
protected:
    int x, y;            
    float speed;           
    std::string objectType;  
    std::string id;

public:
    enum class Direction { Up, Down, Left, Right }; 
 
    virtual void Move(Direction dir);
    virtual void Teleport(int newX, int newY);

    auto GetCoordinates() const;
    const std::string& GetId() const;
};