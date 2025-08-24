#pragma once
#include "../Characters/characters.h"
#include "../TVector/tvector.h"
#include <string>

class Warrior : public Character {
private:
    int rage;               
    bool berserk_mode;       
    TVector<std::string> enhancements; 

public:
    Warrior();

    void shield_bash(Character* target);

    void attack(Character* target) override;

    void toggle_berserk_mode();

    void add_enhancement(const std::string& enhancement);

    int get_rage() const;

    bool is_berserk() const;

    void use_rage_ability();
    void remove_enhancement(const std::string& enhancement);
    void clear_enhancements();
    const TVector<std::string>& get_enhancements() const;
};