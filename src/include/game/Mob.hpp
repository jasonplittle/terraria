#pragma once

#include <memory>
#include <array>

#include <glm/glm.hpp>

#include "Sprite.hpp"

#include "UtilLib.hpp"

#include "World.hpp"

// IVec2 groundedArmAnimFrame = {};


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
        PANTS,
        PARTS_COUNT
    };

public:
    Mob();

    void UpdatePosition(float dx, float dy);

    const std::array<std::unique_ptr<Sprite>, MobPart::PARTS_COUNT>& GetSprites() const { return m_sprites; }

    Vec2 GetSize() const { return m_size; }
    Vec2 GetPosition() const { return m_position; }
    bool IsMovingRight() const { return m_isMovingRight; }
    void Update(float deltaTime, World& world);
    bool IsInAir() const { return m_isInAir; }

private:
    Vec2 m_position = {20.f, 1500.f};
    Vec2 m_size = {24.0f, 24.0f};
    Vec2 m_collideRadii = {8.0f, 20.0f}; // x starts middle, y starts bottom

    bool m_isMovingRight = true;
    bool m_isInAir = true;

    std::array<std::unique_ptr<Sprite>, MobPart::PARTS_COUNT> m_sprites;

    Vec2 m_vel = { 0.f, 0.f };

    float m_velocity = 100.f;

    float m_animSpeed = 0.08;
    float m_animTimer = 0.0;
    int m_animframe = 0; 


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