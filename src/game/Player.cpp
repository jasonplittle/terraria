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





void Player::UpdateCreative(float deltaTime, bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, World& world)
{
    int velocity = 200;

    if (isMovingLeft)
    {
        m_vel.x = -velocity;
        m_isMovingRight = false;
    }

    if (isMovingRight)
    {
        m_vel.x = velocity;
        m_isMovingRight = true;
    }

    if (isMovingDown)
    {
        m_vel.y = -velocity;
    }

    if (isMovingUp)
    {
        m_vel.y = velocity;
    }

    if (!isMovingLeft && !isMovingRight)
    {
        m_vel.x = 0;
    }

    if (!isMovingUp && !isMovingDown)
    {
        m_vel.y = 0;
    }

    m_playerPosition.x += m_vel.x * deltaTime;
    m_playerPosition.y += m_vel.y * deltaTime;

}

float padding = 1.0f;

int GRAVITY = -1800.0f;
float JUMP_VELOCITY = 650.0f;

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

void Player::Update(float deltaTime, bool isMovingUp, bool isMovingDown, bool isMovingLeft, bool isMovingRight, World& world)
{    
    // bool collideBottom = world.IsSolid(m_playerPosition.x - m_collideRadii.x + padding, m_playerPosition.y) || world.IsSolid(m_playerPosition.x + m_collideRadii.x - padding, m_playerPosition.y);
    // bool collideTop = world.IsSolid(m_playerPosition.x - m_collideRadii.x + padding, m_playerPosition.y + m_collideRadii.y) || world.IsSolid(m_playerPosition.x + m_collideRadii.x - padding, m_playerPosition.y + m_collideRadii.y);
    // bool collideLeft = world.IsSolid(m_playerPosition.x - m_collideRadii.x, m_playerPosition.y + padding) || world.IsSolid(m_playerPosition.x - m_collideRadii.x, m_playerPosition.y + m_collideRadii.y - padding);
    // bool collideRight = world.IsSolid(m_playerPosition.x + m_collideRadii.x, m_playerPosition.y + padding) || world.IsSolid(m_playerPosition.x + m_collideRadii.x, m_playerPosition.y + m_collideRadii.y - padding);

    if (isMovingLeft)
    {
        m_vel.x = -m_velocity;
        m_isMovingRight = false;
    }

    if (isMovingRight)
    {
        m_vel.x = m_velocity;
        m_isMovingRight = true;
    }

    if (!isMovingLeft && !isMovingRight)
    {
        m_vel.x = 0;
    }



    m_playerPosition.x += m_vel.x * deltaTime;

    int left = worldToTile(m_playerPosition.x - m_collideRadii.x);
    int right = worldToTile(m_playerPosition.x + m_collideRadii.x);
    int top = worldToTile(m_playerPosition.y + m_collideRadii.y);
    int bottom = worldToTile(m_playerPosition.y);


    std::cout << "Player position: " << m_playerPosition.x << ", " << m_playerPosition.y << " | " << (int)std::floor(m_playerPosition.x / TILE_SIZE) << std::endl;


    for (int y = bottom; y <= top; y++)
    {
        for (int x = left; x <= right; x++)
        {
            if (!world.IsSolid(x, y)) continue;

            float tileLeft  = x * TILE_SIZE;
            float tileRight = tileLeft + TILE_SIZE;

            if (Intersects({{m_playerPosition.x - m_collideRadii.x, m_playerPosition.y}, {m_collideRadii.x * 2, m_collideRadii.y}}, {{x * TILE_SIZE, y * TILE_SIZE}, {TILE_SIZE, TILE_SIZE}}))
            {

                if (m_vel.x > 0.0f)
                {
                    // std::cout << "Collide player right: " << tileLeft << " " << m_playerPosition.x << std::endl;

                    m_playerPosition.x = tileLeft - m_collideRadii.x;
                    m_vel.x = 0.0f;
                }
                else if (m_vel.x < 0.0f)
                {
                    // std::cout << "Collide player left: " << tileRight << " " << m_playerPosition.x << std::endl;

                    m_playerPosition.x = tileRight + m_collideRadii.x;
                    m_vel.x = 0.0f;
                }
            }

            
        }
    }

    if (isMovingUp && !m_isInAir)
    {
        m_vel.y = JUMP_VELOCITY;
        m_isInAir = true;
    }

    m_isInAir = true;
    m_vel.y += GRAVITY * deltaTime;


    m_playerPosition.y += m_vel.y * deltaTime;

    left = worldToTile(m_playerPosition.x - m_collideRadii.x);
    right = worldToTile(m_playerPosition.x + m_collideRadii.x);
    top = worldToTile(m_playerPosition.y + m_collideRadii.y);
    bottom = worldToTile(m_playerPosition.y);


    for (int y = bottom; y <= top; y++)
    {
        for (int x = left; x <= right; x++)
        {
            if (!world.IsSolid(x, y)) continue;

            float tileBottom  = y * TILE_SIZE;
            float tileTop = tileBottom + TILE_SIZE;

            if (Intersects({{m_playerPosition.x - m_collideRadii.x, m_playerPosition.y}, {m_collideRadii.x * 2, m_collideRadii.y}}, {{x * TILE_SIZE, y * TILE_SIZE}, {TILE_SIZE, TILE_SIZE}}))
            {

                if (m_vel.y > 0.0f)
                {
                    // std::cout << "Collide player top: " << tileBottom << " " << m_playerPosition.y << std::endl;

                    m_playerPosition.y = tileBottom - m_collideRadii.y;
                    m_vel.y = 0.0f;

                }
                else if (m_vel.y < 0.0f)
                {
                    // std::cout << "Collide player bottom: " << tileTop << " " << m_playerPosition.y << std::endl;

                    m_playerPosition.y = tileTop;
                    m_vel.y = 0.0f;
                    m_isInAir = false;
                }
            }
        }
    }




    // int minX = floor(left   / TILE_SIZE);
    // int maxX = floor(right  / TILE_SIZE);
    // int minY = floor(bottom / TILE_SIZE);
    // int maxY = floor(top    / TILE_SIZE);

    

    // for (int y = minY; y <= maxY; y++) {
    //     for (int x = minX; x <= maxX; x++) {
    //         if (!world.IsSolid(x, y)) continue;

    //         if (right > x && left < x + TILE_SIZE && top > y && bottom < y + TILE_SIZE)
    //         {
    //             m_playerPosition.x -= m_vel.x * deltaTime;
    //         }
    //     }
    // }

    // m_playerPosition.y += m_vel.y * deltaTime;

    // for (int y = minY; y <= maxY; y++) {
    //     for (int x = minX; x <= maxX; x++) {
    //         if (!world.IsSolid(x, y)) continue;

    //         if (right > x && left < x + TILE_SIZE && top > y && bottom < y + TILE_SIZE)
    //         {
    //             m_playerPosition.y -= m_vel.y * deltaTime;
    //         }
    //     }
    // }


    // bool collideLeft = world.IsSolid(left) || world.IsSolid(m_playerPosition.x - m_collideRadii.x, m_playerPosition.y + m_collideRadii.y - padding);
    // bool collideRight = world.IsSolid(m_playerPosition.x + m_collideRadii.x, m_playerPosition.y + padding) || world.IsSolid(m_playerPosition.x + m_collideRadii.x, m_playerPosition.y + m_collideRadii.y - padding);
    // bool collideTop = world.IsSolid(m_playerPosition.x - m_collideRadii.x + padding, m_playerPosition.y + m_collideRadii.y) || world.IsSolid(m_playerPosition.x + m_collideRadii.x - padding, m_playerPosition.y + m_collideRadii.y);
    // bool collideBottom = world.IsSolid(m_playerPosition.x - m_collideRadii.x + padding, m_playerPosition.y) || world.IsSolid(m_playerPosition.x + m_collideRadii.x - padding, m_playerPosition.y);
    
    



    // m_playerPosition.y += m_vel.y * deltaTime;
    // // m_vel.y += GRAVITY * deltaTime;

    // if (collideBottom)
    // {
    //     m_vel.y = 0;
    //     m_isInAir = false;
    // }
    // if (isMovingUp && !m_isInAir)
    // {
    //     m_vel.y = JUMP_VELOCITY;
    //     m_isInAir = true;
    // }
    // if (collideTop)
    // {
    //     m_vel.y = 0;
    // }

    // // if (collideRight || collideRight)
    // // {
    // //     m_vel.x = 0;
    // // }

    // if (isMovingLeft)
    // {
    //     if (!collideLeft)
    //     {
    //         // m_vel.x = -m_velocity; // Change to accel, clamp to max speed
    //         m_playerPosition.x -= m_vel.x * deltaTime;
    //     }
    //     m_isMovingRight = false;
    // }

    // // std::cout << "Left: " << std::boolalpha << collideLeft ;


    // if (isMovingRight)
    // {
    //     if (!collideRight)
    //     {
    //         // m_vel.x = m_velocity; // Change to accel, clamp to max speed

    //         m_playerPosition.x += m_vel.x * deltaTime;
    //     }
    //     m_isMovingRight = true;
    // }

    
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




    // if (world.IsSolid(m_playerPosition.x, m_playerPosition.y))
    // {
        // m_isInAir = false;
    // }


}





