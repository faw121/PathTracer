#pragma once

#include <util/common.h>

class Interval
{
public:
    float m_min {0.f};
    float m_max {0.f};

    Interval(float min, float max): m_min(min), m_max(max) {}

    bool contains(float x) const { return x >= m_min && x <= m_max; }

    bool surrounds(float x) const { return x > m_min && x < m_max; }

    static const Interval empty, universe;
};

inline const Interval Interval::empty(INF, -INF);
inline const Interval Interval::universe(-INF, INF);