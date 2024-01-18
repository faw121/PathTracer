#include <path_tracer.h>

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <3rdParty/stb_image_write.h>

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

glm::vec3 PathTracer::rayColor(Ray& ray)
{
    glm::vec3 unit_direction = ray.direction();
    float     a              = 0.5f * (unit_direction.y + 1.f);

    glm::vec3 ray_color;

    auto back_ground_color = (1.f - a) * glm::vec3{1.f, 1.f, 1.f} + a * glm::vec3 {0.5f, 0.7f, 1.0f};
    ray_color              = back_ground_color;

    HitPoint hit_point;
    if (m_world->hit(ray, hit_point)) {
        ray_color =
            0.5f * glm::vec3 {hit_point.m_normal.x + 1.f, hit_point.m_normal.y + 1.f, hit_point.m_normal.z + 1.f};
    }
    return ray_color;
}

void PathTracer::render()
{
    for (int j = 0; j < m_frame_height; j++) {
        for (int i = 0; i < m_frame_width; i++) {
            auto pixel_center =
                m_pixel00_position + static_cast<float>(i) * m_pixel_delta_u + static_cast<float>(j) * m_pixel_delta_v;
            auto ray_direction = glm::normalize(pixel_center - m_camera->m_position);
            Ray  ray(m_camera->m_position, ray_direction);

            auto pixel_color = rayColor(ray);

            m_frame_buffer.set(i, j, pixel_color);
            // m_frame_buffer.set(i, j, 255.f * glm::vec4(pixel_color, 1.f));

        }
    }
    stbi_write_bmp("out3.bmp", m_frame_buffer.width(), m_frame_buffer.height(), 4, m_frame_buffer.data());
}
