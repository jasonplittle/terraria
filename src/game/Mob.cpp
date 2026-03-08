#include "Mob.hpp"

#include <iostream>


Mob::Mob()
{

    Vec4 eyeColor = {0.2, 0.5, 0.7, 1.0};
	Vec4 skinColor = {236 / 255.f, 161 / 255.f, 130 / 255.f, 1.0f};
	// Vec4 hairColor = {55 / 255.f, 31 / 255.f, 24 / 255.f, 1.0};
	// Vec4 clothesColor = {189 / 255.f, 30 / 255.f, 73 / 255.f, 1.0};
	Vec4 pantsColor = {33 / 255.f, 14 / 255.f, 30 / 255.f, 1.0};

    Vec2 spriteSize = { 38, 54 };

    m_sprites[MobPart::HEAD] = std::make_unique<Sprite>("resources/Player_0_0.png", spriteSize, IVec2{0, 0});
    m_sprites[MobPart::EYEWHITE] = std::make_unique<Sprite>("resources/Player_0_1.png", spriteSize, IVec2{0, 0});
    m_sprites[MobPart::EYE] = std::make_unique<Sprite>("resources/Player_0_2.png", spriteSize, IVec2{0, 0});
    // m_sprites[PlayerPart::HAIR] = std::make_unique<Sprite>("resources/playerHair/Player_Hair_1.png", spriteSize, IVec2{0, 0});
    m_sprites[MobPart::LEFT_ARM] = std::make_unique<Sprite>("resources/Player_0_7.png", spriteSize, IVec2{2, 3});
    m_sprites[MobPart::TORSO] = std::make_unique<Sprite>("resources/Player_0_3.png", spriteSize, IVec2{0, 0});
    m_sprites[MobPart::RIGHT_ARM] = std::make_unique<Sprite>("resources/Player_0_7.png", spriteSize, IVec2{2, 1});
    m_sprites[MobPart::LEGS] = std::make_unique<Sprite>("resources/Player_0_10.png", spriteSize, IVec2{0, 0});
    // m_sprites[PlayerPart::CLOTHES] = std::make_unique<Sprite>("resources/Player_0_6.png", spriteSize, IVec2{0, 0});
    m_sprites[MobPart::PANTS] = std::make_unique<Sprite>("resources/Player_0_11.png", spriteSize, IVec2{0, 0});

    m_sprites[MobPart::EYE]->SetColor(eyeColor);
    // m_sprites[PlayerPart::HAIR]->SetColor(hairColor);
    m_sprites[MobPart::HEAD]->SetColor(skinColor);
    m_sprites[MobPart::LEGS]->SetColor(skinColor);
    m_sprites[MobPart::LEFT_ARM]->SetColor(skinColor);
    m_sprites[MobPart::RIGHT_ARM]->SetColor(skinColor);
    // m_sprites[PlayerPart::CLOTHES]->SetColor(clothesColor);
    // m_sprites[PlayerPart::PANTS]->SetColor(pantsColor);

}

void Mob::UpdatePosition(float dx, float dy)
{
    m_position.x += dx;
    m_position.y += dy;

    if (dx > 0)
    {
        m_isMovingRight = true;
    }

    if (dx < 0)
    {
        m_isMovingRight = false;
    }
}


void Mob::Update(float deltaTime, World& world)
{    
    m_isInAir = true;
    m_vel.y += GRAVITY * deltaTime;
    m_position.y += m_vel.y * deltaTime;

    int left = worldToTile(m_position.x - m_collideRadii.x);
    int right = worldToTile(m_position.x + m_collideRadii.x);
    int top = worldToTile(m_position.y + m_collideRadii.y);
    int bottom = worldToTile(m_position.y);

    for (int y = bottom; y <= top; y++)
    {
        for (int x = left; x <= right; x++)
        {
            if (!world.IsSolid(x, y)) continue;

            float tileBottom  = y * TILE_SIZE;
            float tileTop = tileBottom + TILE_SIZE;

            if (Intersects({{m_position.x - m_collideRadii.x, m_position.y}, {m_collideRadii.x * 2, m_collideRadii.y}}, {{x * TILE_SIZE, y * TILE_SIZE}, {TILE_SIZE, TILE_SIZE}}))
            {

                if (m_vel.y > 0.0f)
                {
                    // std::cout << "Collide player top: " << tileBottom << " " << m_playerPosition.y << std::endl;

                    m_position.y = tileBottom - m_collideRadii.y;
                    m_vel.y = 0.0f;

                }
                else if (m_vel.y < 0.0f)
                {
                    // std::cout << "Collide player bottom: " << tileTop << " " << m_playerPosition.y << std::endl;

                    m_position.y = tileTop;
                    m_vel.y = 0.0f;
                    m_isInAir = false;
                }
            }
        }
    }
        
    if (m_isInAir)
    {
        m_sprites[MobPart::LEFT_ARM]->SetAtlasPosition(IVec2{2, 3});
        m_sprites[MobPart::RIGHT_ARM]->SetAtlasPosition(IVec2{2, 1});
    }
    else
    {
        // todo select correct animation frame
        m_sprites[MobPart::LEFT_ARM]->SetAtlasPosition(IVec2{2, 2});
        m_sprites[MobPart::RIGHT_ARM]->SetAtlasPosition(IVec2{2, 0});
    }


}
