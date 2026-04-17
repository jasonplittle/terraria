#pragma once


class DayLighting
{
public:
    DayLighting() = default;

    void Update(float deltaTime);

    float GetLighting() const;

private:
    float m_timeOfDay = 0.5f;
    const float m_dayLength = 120.f;


};