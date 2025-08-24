#pragma once
#include "../Characters/characters.h"
#include <chrono>

class Enemy : public Character {
private:
    float m_damage;
    float action_cooldown;
    bool is_timer_active;
    std::chrono::steady_clock::time_point last_action_time;
    Character* current_target;

public:
    Enemy(int x, int y, float health, float damage, float cooldown,
        float speed, const std::string& name, int armor = 0);

    void update(float delta_time);
    void start_timer();
    void stop_timer();
    bool is_action_ready() const;
    void perform_action();

    void set_target(Character* target) { current_target = target; }

    void attack(Character* target) override;
};