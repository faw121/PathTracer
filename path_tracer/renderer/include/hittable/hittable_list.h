# pragma once

#include <hittable/hittable.h>

#include <memory>
#include <vector>

class HittableList: public Hittable
{
public:
    std::vector<std::shared_ptr<Hittable>> m_objects;

    void clear() { m_objects.clear(); }

    void add(std::shared_ptr<Hittable> object)
    {
        m_objects.push_back(object);
    }

    bool hit(const Ray& ray, HitPoint& hit_point, float t_max=Infinity, float t_min=0.001f) override
    {
        float t_closest = t_max;

        HitPoint temp_hit_point;

        bool hit_anything = false;

        for (const auto& object: m_objects) {
            if (object->hit(ray, temp_hit_point, t_closest)) {
                hit_anything = true;
                t_closest = temp_hit_point.m_t;
                hit_point = temp_hit_point;
            }
        }

        return hit_anything;
    }
    
};