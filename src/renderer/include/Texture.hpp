#pragma once

#include "Renderer.hpp"

class Texture
{
public:

    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }

private:
    unsigned int m_renderer_id;
    std::string m_filpath;
    unsigned char* m_local_buffer;
    int m_height, m_width, m_bpp;
};