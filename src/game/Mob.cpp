#include "Mob.hpp"

#include <iostream>


Mob::Mob(float x, float y)
 : m_position{x, y}
{

    Vec4 eyeColor = {1.0, 0.2, 0.2, 1.0};
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
    m_sprites[MobPart::CLOTHES] = std::make_unique<Sprite>("resources/Player_0_6.png", spriteSize, IVec2{0, 0});
    m_sprites[MobPart::PANTS] = std::make_unique<Sprite>("resources/Player_0_11.png", spriteSize, IVec2{0, 0});

    m_sprites[MobPart::EYE]->SetColor(eyeColor);
    // m_sprites[PlayerPart::HAIR]->SetColor(hairColor);
    m_sprites[MobPart::HEAD]->SetColor(skinColor);
    m_sprites[MobPart::LEGS]->SetColor(skinColor);
    m_sprites[MobPart::LEFT_ARM]->SetColor(skinColor);
    m_sprites[MobPart::RIGHT_ARM]->SetColor(skinColor);
    // m_sprites[MobPart::CLOTHES]->SetColor(clothesColor);
    

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

void Mob::updateIdle(float dt)
{
    // std::cout << "idle" << std::endl;

    m_vel.x = 0;

    m_idleTimer += dt;

    if(m_idleTimer > 2.0f)
    {
        m_state = MobState::Wander;
        m_idleTimer = 0;
    }
}

void Mob::updateWander(float dt)
{
    // std::cout << "wander" << std::endl;

    m_vel.x = (m_isMovingRight ? 1 : -1) * m_velocity;

    m_wanderTimer += dt;

    if(m_wanderTimer > 3.0f)
    {
        m_isMovingRight = (rand() % 2 == 0);
        m_wanderTimer = 0;
    }
}

void Mob::updateChase(float dt, const Player& player)
{
    // std::cout << "chase" << std::endl;

    if(player.GetPlayerPosition().x < m_position.x)
    {
        m_vel.x = -m_velocity;
        m_isMovingRight = false;
    }
    else
    {
        m_vel.x = m_velocity;
        m_isMovingRight = true;
    }
}

void Mob::updateAttack(float dt, Player& player, float distance)
{
    m_vel.x = 0;
    m_attackTimer += dt;

    if (m_attackTimer > 1.0f)
    {
        if (distance < 20.f)
        {
            player.TakeDamage(50.f - distance);
        }
        m_attackTimer = 0.0f;
        m_isAlive = false;
    }

}


void Mob::Update(float deltaTime, Player& player, World& world)
{
    float distance = glm::length(glm::vec2(player.GetPlayerPosition().x, player.GetPlayerPosition().y) - glm::vec2(m_position.x, m_position.y));

    if (distance < 20.f)
    {
        m_state = MobState::Attack;
    }

    if (m_state != MobState::Attack)
    {
        if (distance < 200.0f)
        {
            m_state = MobState::Chase;
        }

        if (m_state == MobState::Chase)
        {
            if (distance > 400.f)
            {
                m_state = MobState::Wander;
            }
        }
    }

    switch(m_state)
    {
        case MobState::Idle:
            updateIdle(deltaTime);
            m_sprites[MobPart::CLOTHES]->SetColor({100 / 255.f, 161 / 255.f, 130 / 255.f, 1.0f});
            break;

        case MobState::Wander:
            updateWander(deltaTime);
            m_sprites[MobPart::CLOTHES]->SetColor({236 / 255.f, 161 / 255.f, 50 / 255.f, 1.0f});
            break;

        case MobState::Chase:
            updateChase(deltaTime, player);
            m_sprites[MobPart::CLOTHES]->SetColor({236 / 255.f, 100 / 255.f, 130 / 255.f, 1.0f});
            break;

        case MobState::Attack:
            updateAttack(deltaTime, player, distance);
            m_sprites[MobPart::CLOTHES]->SetColor({(236 + (m_attackTimer * 18))  / 255.f, (100 + (m_attackTimer * 155)) / 255.f, (130 + (m_attackTimer * 125)) / 255.f, 1.0f});
            break;
    }

    // Detect attack
    if (player.IsAttacking() && distance < 20.f)
    {
        if (player.IsMovingRight() && m_position.x - player.GetPlayerPosition().x > 0)
        {
            m_isAlive = false;
        }
        else if (!player.IsMovingRight() && m_position.x - player.GetPlayerPosition().x < 0)
        {
            m_isAlive = false;
        }
    }

    m_position.x += m_vel.x * deltaTime;

    int left = worldToTile(m_position.x - m_collideRadii.x);
    int right = worldToTile(m_position.x + m_collideRadii.x);
    int top = worldToTile(m_position.y + m_collideRadii.y);
    int bottom = worldToTile(m_position.y);


    for (int y = bottom; y <= top; y++)
    {
        for (int x = left; x <= right; x++)
        {
            if (!world.IsSolid(x, y)) continue;

            float tileLeft  = x * TILE_SIZE;
            float tileRight = tileLeft + TILE_SIZE;

            if (Intersects({{m_position.x - m_collideRadii.x, m_position.y}, {m_collideRadii.x * 2, m_collideRadii.y}}, {{x * TILE_SIZE, y * TILE_SIZE}, {TILE_SIZE, TILE_SIZE}}))
            {
                if (m_vel.x > 0.0f)
                {
                    m_position.x = tileLeft - m_collideRadii.x;
                    m_vel.x = 0.0f;
                }
                else if (m_vel.x < 0.0f)
                {
                    m_position.x = tileRight + m_collideRadii.x;
                    m_vel.x = 0.0f;
                }
            }   
        }
    }


    // Detect jump
    if (abs(m_vel.x) > 0 && !m_isInAir && distance > TILE_SIZE)
    {
        bool sol = world.IsSolid(worldToTile(m_position.x + ((m_vel.x > 0 ? TILE_SIZE : -TILE_SIZE))), worldToTile(m_position.y));

        // std::cout << worldToTile(m_position.x) << ", " << worldToTile(m_position.y) << " - " << sol << std::endl;

        if (sol)
        {
            m_vel.y = JUMP_VELOCITY;
        }
    }



    m_isInAir = true;
    m_vel.y += GRAVITY * deltaTime;
    m_position.y += m_vel.y * deltaTime;

    left = worldToTile(m_position.x - m_collideRadii.x);
    right = worldToTile(m_position.x + m_collideRadii.x);
    top = worldToTile(m_position.y + m_collideRadii.y);
    bottom = worldToTile(m_position.y);


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
                    m_position.y = tileBottom - m_collideRadii.y;
                    m_vel.y = 0.0f;

                }
                else if (m_vel.y < 0.0f)
                {
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

    if (m_state == MobState::Wander || m_state == MobState::Chase)
    {
        m_animTimer += deltaTime;

        if (m_animTimer >= m_animSpeed)
        {
            m_animTimer -= m_animSpeed;
            m_animframe++;
            m_animframe %= 14;
            // m_animframe %= 5;

            m_sprites[MobPart::PANTS]->SetAtlasPosition(IVec2{0, m_animframe});
            m_sprites[MobPart::LEGS]->SetAtlasPosition(IVec2{0, m_animframe});

            // m_sprites[PlayerPart::RIGHT_ARM]->SetAtlasPosition(runningArmAnimFrames[m_animframe]);
        }
    }

}
