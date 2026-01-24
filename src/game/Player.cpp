#include "Player.hpp"


Player::Player()
{
    Vec2 spriteSize = { 38, 54 };

    m_sprites[PlayerPart::HEAD] = std::make_unique<Sprite>("resources/Player_0_0.png", spriteSize);
    m_sprites[PlayerPart::EYEWHITE] = std::make_unique<Sprite>("resources/Player_0_1.png", spriteSize);
    m_sprites[PlayerPart::EYE] = std::make_unique<Sprite>("resources/Player_0_2.png", spriteSize);
    m_sprites[PlayerPart::TORSO] = std::make_unique<Sprite>("resources/Player_0_3.png", spriteSize);
    m_sprites[PlayerPart::RIGHT_ARM] = std::make_unique<Sprite>("resources/Player_0_7.png", spriteSize);
    m_sprites[PlayerPart::LEGS] = std::make_unique<Sprite>("resources/Player_0_10.png", spriteSize);
    m_sprites[PlayerPart::CLOTHES] = std::make_unique<Sprite>("resources/Player_0_6.png", spriteSize);
    m_sprites[PlayerPart::PANTS] = std::make_unique<Sprite>("resources/Player_0_11.png", spriteSize);
}

void Player::UpdatePosition(float dx, float dy)
{
    m_playerPosition.x += dx;
    m_playerPosition.y += dy;

    if (dx > 0)
    {
        m_isMovingRight = true;
    }

    if (dx < 0)
    {
        m_isMovingRight = false;
    }
}