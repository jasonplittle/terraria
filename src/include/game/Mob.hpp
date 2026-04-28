#pragma once

#include <memory>
#include <array>

#include <glm/glm.hpp>

#include "Sprite.hpp"

#include "UtilLib.hpp"

#include "World.hpp"
#include "Player.hpp"


class Mob
{
    enum MobPart
    {
        HEAD,
        EYEWHITE,
        EYE,
        LEFT_ARM,
        TORSO,
        RIGHT_ARM,
        LEGS,
        CLOTHES,
        PANTS,
        PARTS_COUNT
    };

    enum class MobState
    {
        Idle,
        Wander,
        Chase,
        Attack
    };

public:
    Mob(float x, float y);

    void UpdatePosition(float dx, float dy);

    const std::array<std::unique_ptr<Sprite>, MobPart::PARTS_COUNT>& GetSprites() const { return m_sprites; }

    Vec2 GetSize() const { return m_size; }
    Vec2 GetPosition() const { return m_position; }
    bool IsMovingRight() const { return m_isMovingRight; }
    void Update(float deltaTime, Player& player, World& world);
    bool IsInAir() const { return m_isInAir; }
    bool IsAlive() const { return m_isAlive; }

private:
    void updateIdle(float dt);
    void updateWander(float dt);
    void updateChase(float dt, const Player& player);
    void updateAttack(float dt, Player& player, float distance);

    bool m_isAlive = true;

    MobState m_state = MobState::Idle;
    float m_idleTimer = 0;
    float m_wanderTimer = 0;
    float m_attackTimer = 0;

    Vec2 m_position;
    Vec2 m_size = {24.0f, 24.0f};
    Vec2 m_collideRadii = {8.0f, 20.0f}; // x starts middle, y starts bottom

    bool m_isMovingRight = true;
    bool m_isInAir = true;

    std::array<std::unique_ptr<Sprite>, MobPart::PARTS_COUNT> m_sprites;

    Vec2 m_vel = { 0.f, 0.f };

    float m_velocity = 80.f;

    float m_animSpeed = 0.08;
    float m_animTimer = 0.0;
    int m_animframe = 0;
    
    static constexpr float JUMP_VELOCITY = 400.0f;


    inline int worldToTile(float world)
    {
        return (int)std::floor(world / TILE_SIZE);
    }

    struct AABB {
        glm::vec2 pos;   // bottom-left (or top-left, just be consistent)
        glm::vec2 size;
    };

    inline bool Intersects(const AABB& a, const AABB& b) {
        return !(a.pos.x + a.size.x <= b.pos.x ||
                a.pos.x >= b.pos.x + b.size.x ||
                a.pos.y + a.size.y <= b.pos.y ||
                a.pos.y >= b.pos.y + b.size.y);
    }

    static constexpr int GRAVITY = -1800.0f;
};