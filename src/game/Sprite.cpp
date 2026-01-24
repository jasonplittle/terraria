#include "Sprite.hpp"


Sprite::Sprite(const std::string& textureFilePath, Vec2 spriteTextureSize)
{
    m_texture = std::make_unique<Texture>(textureFilePath);

    IVec2 atlasSize{ m_texture->GetWidth(), m_texture->GetHeight() };
    Vec2 pixelSize = { 1.0f / atlasSize.x, 1.0f / atlasSize.y };
    Vec2 atlasPadding = {pixelSize.x * 0.25f, pixelSize.y * 0.25f };
    Vec2 spriteSizeNormalised = { spriteTextureSize.x * pixelSize.x, spriteTextureSize.y * pixelSize.y };

    // float x0 = atlasPadding.x;
    // float x1 = atlasPadding.x + spriteSizeNormalised.x;
    // float y0 = 1.0f - atlasPadding.y - spriteSizeNormalised.y;
    // float y1 = atlasPadding.y;

    float x0 = 0.0f;
    float x1 = spriteSizeNormalised.x;
    float y0 = 1.0f - spriteSizeNormalised.y;
    float y1 = 1.0f;


    // float x0 = 0.0f;
    // float x1 = spriteTextureSize.x / atlasSize.x;
    // float y0 = 1.0f - (spriteTextureSize.y / atlasSize.y);
    // float y1 = 1.0f;

    m_UV = { x0, y0, x1, y1 };
}

