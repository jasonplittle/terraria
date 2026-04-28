#pragma once

#include <memory>
#include <array>

#include <glm/glm.hpp>

#include "Sprite.hpp"

#include "UtilLib.hpp"

#include "World.hpp"

class World; // Forward declaration


// IVec2 groundedArmAnimFrame = {};



class Player
{
    enum PlayerPart
    {
        HEAD,
        EYEWHITE,
        EYE,
        HAIR,
        LEFT_ARM,
        TORSO,
        RIGHT_ARM,
        CLOTHES,
        LEGS,
        PANTS,
        PARTS_COUNT
    };

public:
    Player();

    void UpdatePosition(float dx, float dy);

    const std::array<std::unique_ptr<Sprite>, PlayerPart::PARTS_COUNT>& GetSprites() const { return m_sprites; }

    Vec2 GetPlayerSize() const { return m_playerSize; }
    Vec2 GetPlayerPosition() const { return m_playerPosition; }
    bool IsMovingRight() const { return m_isMovingRight; }
    void Update(float deltaTime, bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, bool isAttacking, World& world);
    void UpdateCreative(float deltaTime, bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, World& world);
    bool IsInAir() const { return m_isInAir; }
    bool IsMining() const { return m_isMining; }
    bool IsAttacking() const { return m_isAttacking; }
    void TakeDamage(float damage);

private:
    Vec2 m_playerPosition = {0.f, 1500.f};
    Vec2 m_playerSize = {32.0f, 32.0f};
    Vec2 m_collideRadii = {10.0f, 30.0f}; // x starts middle, y starts bottom

    float m_health = 100.0f;

    bool m_isMovingRight = true;
    bool m_isInAir = true;
    bool m_isMining = false;
    bool m_isAttacking = false;

    std::array<std::unique_ptr<Sprite>, PlayerPart::PARTS_COUNT> m_sprites;

    Vec2 m_vel = { 0.f, 0.f };

    float m_velocity = 200.f;

    float m_animSpeed = 0.08;
    float m_animTimer = 0.0;
    int m_animframe = 0; 


    static constexpr int GRAVITY = -1800.0f;
    static constexpr float JUMP_VELOCITY = 650.0f;

    struct AABB {
        glm::vec2 pos;   // bottom-left (or top-left, just be consistent)
        glm::vec2 size;
    };

    inline int worldToTile(float world)
    {
        return (int)std::floor(world / TILE_SIZE);
    }

    inline bool Intersects(const AABB& a, const AABB& b) {
        return !(a.pos.x + a.size.x <= b.pos.x ||
                a.pos.x >= b.pos.x + b.size.x ||
                a.pos.y + a.size.y <= b.pos.y ||
                a.pos.y >= b.pos.y + b.size.y);
    }

    static constexpr std::array<IVec2, 5> runningArmAnimFrames = {IVec2{2, 1}, IVec2{3, 1}, IVec2{4, 1}, IVec2{5, 1}, IVec2{6, 1}};
};