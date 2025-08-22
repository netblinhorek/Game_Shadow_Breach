// Enemy.cpp
#include "enemy.h"
#include <chrono>

Enemy::Enemy(int x, int y, float health, float damage, float cooldown,
    float speed, const std::string& name, int armor)
    : Character(x, y, health, speed, name, armor),
    m_damage(damage),
    action_cooldown(cooldown),
    is_timer_active(false),
    current_target(nullptr)
{
    start_timer();
}

void Enemy::update(float delta_time) {
    if (is_timer_active && is_action_ready()) {
        perform_action();
        start_timer();
    }
}

void Enemy::start_timer() {
    last_action_time = std::chrono::steady_clock::now();
    is_timer_active = true;
}

void Enemy::stop_timer() {
    is_timer_active = false;
}

bool Enemy::is_action_ready() const {
    if (!is_timer_active) return false;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_action_time).count() / 1000.0f;

    return elapsed >= action_cooldown;
}

void Enemy::perform_action() {
    if (current_target != nullptr) {
        attack(current_target);
    }
}

void Enemy::attack(Character* target) {
    if (target != nullptr) {
        target->take_damage(m_damage);
    }
}