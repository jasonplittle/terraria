#include <memory>

#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"


class BackgroundRenderer
{
public:
    BackgroundRenderer();

    void Render(Vec2 screenSize);



private:
    std::unique_ptr<Texture> m_texture;
    std::unique_ptr<Shader> m_shader;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;



};
