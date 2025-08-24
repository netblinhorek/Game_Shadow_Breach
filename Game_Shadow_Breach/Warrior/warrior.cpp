#include "../Warrior/warrior.h"
#include <stdexcept>

Warrior::Warrior()
    : Character(0, 0, 100.0f, 5.0f, "Warrior", 10),
    rage(0),
    berserk_mode(false)
{
}

void Warrior::shield_bash(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("цель не может быть нулевой");
    }

    if (rage >= 10) {
        target->take_damage(15 + rage / 2);
        rage -= 10;
    }
    else {
        target->take_damage(10);
        rage += 5;
    }
}

void Warrior::attack(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("цель не может быть нулевой");
    }

    if (berserk_mode) {
        target->take_damage(20 + rage);
        rage += 3;
    }
    else {
        target->take_damage(10 + rage / 2);
        rage += 2;
    }

    if (rage > 100) {
        rage = 100;
    }
}

void Warrior::toggle_berserk_mode() {
    berserk_mode = !berserk_mode;
    if (berserk_mode) {
        enhancements.push_back("Berserk");
        rage += 20;
        if (rage > 100) rage = 100;
    }
    else {
        for (size_t i = 0; i < enhancements.size(); ++i) {
            if (enhancements[i] == "Berserk") {
                enhancements.erase(i);
                break;
            }
        }
        rage -= 10;
        if (rage < 0) rage = 0;
    }
}

void Warrior::add_enhancement(const std::string& enhancement) {
    if (enhancement.empty()) {
        throw std::invalid_argument("улучшение не может быть пустым");
    }
    enhancements.push_back(enhancement);

    if (enhancement == "Strength") {
        rage += 15;
    }

    if (rage > 100) rage = 100;
}

int Warrior::get_rage() const {
    return rage;
}

bool Warrior::is_berserk() const {
    return berserk_mode;
}

void Warrior::use_rage_ability() {
    if (rage >= 30) {
        rage -= 30;
    }
    else {
        throw std::runtime_error("недостаточно ярости для способности");
    }
}

void Warrior::remove_enhancement(const std::string& enhancement) {
    for (size_t i = 0; i < enhancements.size(); ++i) {
        if (enhancements[i] == enhancement) {
            enhancements.erase(i);
            if (enhancement == "Strength") {
                rage -= 15;
                if (rage < 0) rage = 0;
            }
            break;
        }
    }
}

void Warrior::clear_enhancements() {
    enhancements.clear();
    rage = 0;
}

const TVector<std::string>& Warrior::get_enhancements() const {
    return enhancements;
}