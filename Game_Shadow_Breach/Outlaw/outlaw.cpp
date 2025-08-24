#include "../Outlaw/outlaw.h"
#include <stdexcept>
#include <random>

Outlaw::Outlaw(int id, int x, int y, float speed,
    int health, int armor, int level,
    int stealth, float crit_chance)
    : Character(x, y, health, speed, "Outlaw_" + std::to_string(id), armor),
    stealth(stealth),
    crit_chance(crit_chance)
{
    if (id <= 0) throw std::invalid_argument("»дентификатор должен быть положительным");
    if (stealth < 0) throw std::invalid_argument("—крытность не может быть негативной");
    if (crit_chance < 0.0f || crit_chance > 1.0f) {
        throw std::invalid_argument("¬еро€тность критического удара должна составл€ть от 0 до 1");
    }
}

void Outlaw::backstab(Character& target) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    float roll = dist(gen);
    bool is_critical = (roll <= crit_chance);

    int base_damage = 15 + stealth / 2;

    if (is_critical) {
        target.take_damage(base_damage * 2);
    }
    else {
        target.take_damage(base_damage);
    }

    stealth -= 5;
    if (stealth < 0) stealth = 0;
}

void Outlaw::sneak() {
    stealth += 10;
    if (stealth > 100) {
        stealth = 100;
    }

    if (stealth > 50) {
        crit_chance += 0.1f;
        if (crit_chance > 0.8f) crit_chance = 0.8f;
    }
}

void Outlaw::set_stealth(int new_stealth) {
    if (new_stealth < 0) {
        throw std::invalid_argument("значение скрытности не может быть негативной");
    }
    stealth = new_stealth;
    if (stealth > 100) stealth = 100;
}

void Outlaw::set_crit_chance(float new_chance) {
    if (new_chance < 0.0f || new_chance > 1.0f) {
        throw std::invalid_argument("¬еро€тность критического удара должна составл€ть от 0 до 1");
    }
    crit_chance = new_chance;
}