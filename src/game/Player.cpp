#include "Player.hpp"


Player::Player()
{

    Vec4 eyeColor = {0.2, 0.5, 0.7, 1.0};
	Vec4 skinColor = {236 / 255.f, 161 / 255.f, 130 / 255.f, 1.0f};
	Vec4 hairColor = {55 / 255.f, 31 / 255.f, 24 / 255.f, 1.0};
	Vec4 clothesColor = {189 / 255.f, 30 / 255.f, 73 / 255.f, 1.0};
	Vec4 pantsColor = {33 / 255.f, 14 / 255.f, 30 / 255.f, 1.0};

    Vec2 spriteSize = { 38, 54 };

    m_sprites[PlayerPart::HEAD] = std::make_unique<Sprite>("resources/Player_0_0.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::EYEWHITE] = std::make_unique<Sprite>("resources/Player_0_1.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::EYE] = std::make_unique<Sprite>("resources/Player_0_2.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::TORSO] = std::make_unique<Sprite>("resources/Player_0_3.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::RIGHT_ARM] = std::make_unique<Sprite>("resources/Player_0_7.png", spriteSize, IVec2{2, 0});
    m_sprites[PlayerPart::LEGS] = std::make_unique<Sprite>("resources/Player_0_10.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::CLOTHES] = std::make_unique<Sprite>("resources/Player_0_6.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::PANTS] = std::make_unique<Sprite>("resources/Player_0_11.png", spriteSize, IVec2{0, 0});

    m_sprites[PlayerPart::EYE]->SetColor(eyeColor);
    m_sprites[PlayerPart::HEAD]->SetColor(skinColor);
    m_sprites[PlayerPart::LEGS]->SetColor(skinColor);
    m_sprites[PlayerPart::RIGHT_ARM]->SetColor(skinColor);
    m_sprites[PlayerPart::CLOTHES]->SetColor(clothesColor);
    m_sprites[PlayerPart::PANTS]->SetColor(pantsColor);

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