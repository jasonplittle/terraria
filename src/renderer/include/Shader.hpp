#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:
    Shader(const std::string& filepath);

    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform1f(const std::string& name, float v0);
    void SetUniform1i(const std::string& name, int v0);
    void SetUniform1iv(const std::string& name, unsigned int count, const int* values);
    void SetUniformMat4f(const std::string& name, const glm::mat4& mat);


private:
    unsigned int GetUniformLocation(const std::string& name);

    unsigned int CreateShader(const std::string& vertexSharder, const std::string& fragmentShader);
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);

    unsigned int m_renderer_id;
    std::string m_file_path;
    std::unordered_map<std::string, int> m_uniform_location_cache;
};