#include "DayLighting.hpp"

#include <cmath>

void DayLighting::Update(float deltaTime)
{
    m_timeOfDay += deltaTime / m_dayLength;
    if (m_timeOfDay > 1.0f)
        m_timeOfDay -= 1.0f;

}

float DayLighting::GetLighting() const
{

    float daylight = std::sin(m_timeOfDay * 2.0f * 3.14159f) * 0.5f + 0.5f;
    float lightLevel = 0.2f + daylight * 0.8f;

    return lightLevel;
}