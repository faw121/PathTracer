
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

#include <algorithm>
#include <array>
#include<iostream>
#include <format>
#include <stdint.h>
#include <vector>

#include <camera.h>
#include <ray.h>
#include <model/sphere.h>
#include <basic/frame_buffer.h>


#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <3rdParty/stb_image_write.h>

float asp_ratio = 16.f / 9.f;

int frame_width = 400;
int frame_height = static_cast<int>(frame_width / asp_ratio);
FrameBuffer frame_buffer(frame_width, frame_height);

glm::vec4 rayColor(Ray& r) {
    glm::vec3 unit_direction = r.direction();
    float a = 0.5f * (unit_direction.y + 1.f);
    return (1.f - a) * glm::vec4{1.f, 1.f, 1.f, 1.f} + a * glm::vec4{0.5f, 0.7f, 1.0f, 1.f};
    // return glm::vec3(1.f);
}

int main()
{	
    Camera camera;
    camera.m_position = glm::vec3(0.f);
    camera.m_focal_length = 1.f;

    // adding adding a sphere to the scene
    Sphere sphere;
    sphere.m_center = glm::vec3{0.f, 0.f, -3.f};
    sphere.m_radius = 1.5f;

    glm::vec3 viewport_v{0.f, -2 * glm::tan(camera.m_fov) * camera.m_focal_length, 0.f};
    glm::vec3 viewport_u = {-viewport_v.y * static_cast<float>(frame_width) / frame_height, 0.f, 0.f};

    auto pixel_delta_u = viewport_u / static_cast<float>(frame_width);
    auto pixel_delta_v = viewport_v / static_cast<float>(frame_height);

    auto viewport_upper_left = camera.m_position - viewport_u / 2.f - viewport_v / 2.f - glm::vec3{0.f, 0.f, camera.m_focal_length};
    auto pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);

    for (int j = 0; j < frame_height; j++) {
        for (int i = 0; i < frame_width; i++) {
            auto pixel_center = pixel00_loc + static_cast<float>(i) * pixel_delta_u + static_cast<float>(j) * pixel_delta_v;
            auto ray_direction = glm::normalize(pixel_center - camera.m_position);
            Ray ray(camera.m_position, ray_direction);

            auto pixel_color = 255.f * rayColor(ray);

            auto hit_point = sphere.hit(ray);
            if (hit_point.m_is_hit)
                pixel_color = 255.f * hit_point.m_color;

            frame_buffer.set(i, j, std::array<float, 4>{pixel_color.x, pixel_color.y, pixel_color.z, 255.f});
        }
    }
    stbi_write_bmp("out2.bmp", frame_buffer.width() , frame_buffer.height(), 4, frame_buffer.data());


	return 0;
}