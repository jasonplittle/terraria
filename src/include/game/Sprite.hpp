#pragma once

#include <memory>

#include "Texture.hpp"

#include "UtilLib.hpp"

#include <glm/glm.hpp>


class Sprite
{
public:
    Sprite(const std::string& textureFilePath, Vec2 spriteTextureSize, IVec2 atlasPosition);

    const Texture& GetTexture() const { return *m_texture; }

    Vec4 GetAtlasCoords(bool flipX) const;
    void SetAtlasPosition(IVec2 atlasPosition) { m_atlasPosition = atlasPosition; }
    Vec4 GetColor() const { return m_color; }
    void SetColor(Vec4 color) { m_color = color; }
    
private:
    std::unique_ptr<Texture> m_texture;
    IVec2 m_atlasPosition;
    Vec2 m_spriteSize;
    Vec4 m_color = { 1.0, 1.0, 1.0, 1.0 };

    Vec2 m_spriteTextureSize;
};
