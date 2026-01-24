#pragma once

#include <memory>

#include "Texture.hpp"

#include "UtilLib.hpp"

#include <glm/glm.hpp>


class Sprite
{
public:
    Sprite(const std::string& textureFilePath, Vec2 spriteTextureSize);

    const Texture& GetTexture() const { return *m_texture; }

    Vec4 GetUV() const { return m_UV; }



private:
    std::unique_ptr<Texture> m_texture;
    Vec4 m_UV;
    Vec2 m_spriteSize;
};

