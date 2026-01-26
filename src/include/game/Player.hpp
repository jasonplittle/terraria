#pragma once

#include <memory>
#include <array>

#include <glm/glm.hpp>

#include "Sprite.hpp"

#include "UtilLib.hpp"

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


// IVec2 groundedArmAnimFrame = {};


class Player
{
public:
    Player();

    void UpdatePosition(float dx, float dy);

    const std::array<std::unique_ptr<Sprite>, PlayerPart::PARTS_COUNT>& GetSprites() const { return m_sprites; }

    Vec2 GetPlayerSize() const { return m_playerSize; }
    Vec2 GetPlayerPosition() const { return m_playerPosition; }
    bool IsMovingRight() const { return m_isMovingRight; }
    void Update(float deltaTime, bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight);

private:
    Vec2 m_playerPosition = {0.0f, 0.0f};
    Vec2 m_playerSize = {100.0f, 150.0f};

    bool m_isMovingRight = true;
    bool m_isInAir = true;

    std::array<std::unique_ptr<Sprite>, PlayerPart::PARTS_COUNT> m_sprites;

    float m_velocity = 500.f;

    float m_animSpeed = 0.08;
    float m_animTimer = 0.0;
    int m_animframe = 0; 



    static constexpr std::array<IVec2, 5> runningArmAnimFrames = {IVec2{2, 1}, IVec2{3, 1}, IVec2{4, 1}, IVec2{5, 1}, IVec2{6, 1}};
};