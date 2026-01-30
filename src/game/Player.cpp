#include "Player.hpp"

#include <iostream>


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
    m_sprites[PlayerPart::HAIR] = std::make_unique<Sprite>("resources/playerHair/Player_Hair_1.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::LEFT_ARM] = std::make_unique<Sprite>("resources/Player_0_7.png", spriteSize, IVec2{2, 3});
    m_sprites[PlayerPart::TORSO] = std::make_unique<Sprite>("resources/Player_0_3.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::RIGHT_ARM] = std::make_unique<Sprite>("resources/Player_0_7.png", spriteSize, IVec2{2, 1});
    m_sprites[PlayerPart::LEGS] = std::make_unique<Sprite>("resources/Player_0_10.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::CLOTHES] = std::make_unique<Sprite>("resources/Player_0_6.png", spriteSize, IVec2{0, 0});
    m_sprites[PlayerPart::PANTS] = std::make_unique<Sprite>("resources/Player_0_11.png", spriteSize, IVec2{0, 0});

    m_sprites[PlayerPart::EYE]->SetColor(eyeColor);
    m_sprites[PlayerPart::HAIR]->SetColor(hairColor);
    m_sprites[PlayerPart::HEAD]->SetColor(skinColor);
    m_sprites[PlayerPart::LEGS]->SetColor(skinColor);
    m_sprites[PlayerPart::LEFT_ARM]->SetColor(skinColor);
    m_sprites[PlayerPart::RIGHT_ARM]->SetColor(skinColor);
    m_sprites[PlayerPart::CLOTHES]->SetColor(clothesColor);
    // m_sprites[PlayerPart::PANTS]->SetColor(pantsColor);

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

int GRAVITY = -1800.0f;
float JUMP_VELOCITY = 650.0f;

// void Player::Update(float deltaTime, bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, const World& world)
// {
//     if (m_isInAir)
//     {
//         m_vel.y += GRAVITY * deltaTime;
//     }
//     else
//     {
//         m_vel.y = 0.0f;
//     }

//     m_playerPosition.y += m_vel.y * deltaTime;

//     if (isMovingLeft)
//     {
//         m_playerPosition.x -= m_vel.x * deltaTime;
//         m_isMovingRight = false;
//     }
//     else if (isMovingRight)
//     {
//         m_playerPosition.x += m_vel.x * deltaTime;
//         m_isMovingRight = true;
//     }

//     if (isMovingUp && !m_isInAir)
//     {
//         m_vel.y = JUMP_VELOCITY;
//         m_isInAir = true;
//     }

//     if (world.IsSolid(m_playerPosition.x, m_playerPosition.y))
//     {
//         m_isInAir = false;
//     }

//     // if (m_vel.y < 0)
//     // {
//         // m_isInAir = false;
//     // }

// }

void Player::Update(float deltaTime, bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, const World& world)
{
    m_isInAir = false;

    if (isMovingUp)
    {
        bool collideTop = world.IsSolid(m_playerPosition.x, m_playerPosition.y + m_playerSize.y);
        if (!collideTop)
        {
            m_playerPosition.y += m_velocity * deltaTime;
        }
        
        m_isInAir = true;
    }
    else if (isMovingDown)
    {
        bool collideBottom = world.IsSolid(m_playerPosition.x, m_playerPosition.y);
        if (!collideBottom)
        {
            m_playerPosition.y -= m_velocity * deltaTime;
        }
        m_isInAir = true;
    }

    if (isMovingLeft)
    {
        m_playerPosition.x -= m_velocity * deltaTime;
        m_isMovingRight = false;
    }
    else if (isMovingRight)
    {
        m_playerPosition.x += m_velocity * deltaTime;
        m_isMovingRight = true;
    }
    

    if (m_isInAir)
    {
        m_sprites[PlayerPart::LEFT_ARM]->SetAtlasPosition(IVec2{2, 3});
        m_sprites[PlayerPart::RIGHT_ARM]->SetAtlasPosition(IVec2{2, 1});
    }
    else
    {
        // todo select correct animation frame
        m_sprites[PlayerPart::LEFT_ARM]->SetAtlasPosition(IVec2{2, 2});
        m_sprites[PlayerPart::RIGHT_ARM]->SetAtlasPosition(IVec2{2, 0});
    }


    if (isMovingLeft || isMovingRight)
    {
        m_animTimer += deltaTime;

        if (m_animTimer >= m_animSpeed)
        {
            m_animTimer -= m_animSpeed;
            m_animframe++;
            m_animframe %= 14;
            // m_animframe %= 5;

            m_sprites[PlayerPart::HAIR]->SetAtlasPosition(IVec2{0, m_animframe});
            m_sprites[PlayerPart::PANTS]->SetAtlasPosition(IVec2{0, m_animframe});
            m_sprites[PlayerPart::LEGS]->SetAtlasPosition(IVec2{0, m_animframe});

            // m_sprites[PlayerPart::RIGHT_ARM]->SetAtlasPosition(runningArmAnimFrames[m_animframe]);
        }
    }



    if (world.IsSolid(m_playerPosition.x, m_playerPosition.y))
    {
        // m_isInAir = false;
    }


}


