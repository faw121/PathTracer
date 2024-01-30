#include <path_tracer.h>
#include <util/common_math.h>
#include <material/material.h>

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <3rdParty/stb_image_write.h>

#define SAMPLE_PER_PIXEL 50
#define MAX_TRACE_DEPTH 10
#define PROB_RR 0.8f

bool PathTracer::init()
{
    if (m_camera == nullptr && m_world == nullptr) {
        std::cout << "camera and world not set!" << std::endl;
        return false;
    }

    glm::vec3 viewport_v {0.f, -2 * glm::tan(m_camera->m_fov) * m_camera->m_focal_length, 0.f};
    glm::vec3 viewport_u = {-viewport_v.y * static_cast<float>(m_frame_width) / m_frame_height, 0.f, 0.f};

    m_pixel_delta_u = viewport_u / static_cast<float>(m_frame_width);
    m_pixel_delta_v = viewport_v / static_cast<float>(m_frame_height);

    auto viewport_upper_left =
        m_camera->m_position - viewport_u / 2.f - viewport_v / 2.f - glm::vec3 {0.f, 0.f, m_camera->m_focal_length};
    m_pixel00_position = viewport_upper_left + 0.5f * (m_pixel_delta_u + m_pixel_delta_v);

    return true;
}

glm::vec3 PathTracer::rayColor(Ray& ray, int depth)
{   
    if (depth <= 0)
        return glm::vec3(0.f);

    HitPoint hit_point;

    if (m_world->hit(ray, hit_point)) {
        Ray bounce_ray;
        auto material = hit_point.m_material;
        auto attenuation = glm::vec3(0.f);
        if (!material->scatter(ray, hit_point, attenuation, bounce_ray))
            return glm::vec3(0.f);
        return attenuation * rayColor(bounce_ray, depth - 1);
    }

    glm::vec3 unit_direction = ray.direction();
    float     a              = 0.5f * (unit_direction.y + 1.f);

    auto back_ground_color = (1.f - a) * glm::vec3{1.f, 1.f, 1.f} + a * glm::vec3 {0.5f, 0.7f, 1.0f};

    return back_ground_color;
}

void PathTracer::render()
{
    for (int j = 0; j < m_frame_height; j++) {
        for (int i = 0; i < m_frame_width; i++) {
            glm::vec3 pixel_color{0.f};
            for (int k = 0; k < SAMPLE_PER_PIXEL; k++) {
                auto ray = shootRay(i, j);
                pixel_color += rayColor(ray, MAX_TRACE_DEPTH);
            }

            pixel_color /= static_cast<float>(SAMPLE_PER_PIXEL);

            pixel_color = linearToGamma(pixel_color);
            
            m_frame_buffer.set(i, j, pixel_color);
        }
    }
    stbi_write_bmp("out4.bmp", m_frame_buffer.width(), m_frame_buffer.height(), 4, m_frame_buffer.data());
}

glm::vec3 PathTracer::pixelSampleSquare() const
{
    auto px = -0.5f + randomFloat();
    auto py = -0.5f + randomFloat();
    return px *m_pixel_delta_u + py * m_pixel_delta_v;
}

Ray PathTracer::shootRay(int i, int j) const
{
    auto pixel_center =
                m_pixel00_position + static_cast<float>(i) * m_pixel_delta_u + static_cast<float>(j) * m_pixel_delta_v;
    auto pixel_sample = pixel_center + pixelSampleSquare();

    auto ray_direction = glm::normalize(pixel_sample - m_camera->m_position);
    
    return Ray(m_camera->m_position, ray_direction);
}