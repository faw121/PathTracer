#pragma once

#include <util/frame_buffer.h>
#include <camera.h>
#include <hittable/hittable_list.h>


#include <memory>

class PathTracer
{
public:
    PathTracer(int w, int h) : m_frame_width(w), m_frame_height(h), m_frame_buffer(FrameBuffer(w, h)) {}

    void setCamera(std::shared_ptr<Camera>& camera) { m_camera = camera; }
    void setWorld(std::shared_ptr<HittableList>& world) { m_world = world; }

    bool init();

    glm::vec3 rayColor(Ray& ray, int depth);

    void render();

    std::shared_ptr<Camera>       m_camera {nullptr};
    std::shared_ptr<HittableList> m_world {nullptr};

private:
    glm::vec3 pixelSampleSquare() const;
    Ray shootRay(int i, int j) const;

    glm::vec3 m_pixel_delta_u {0.f};
    glm::vec3 m_pixel_delta_v {0.f};
    glm::vec3 m_pixel00_position {0.f};

    int m_frame_width {1920};
    int m_frame_height {1080};

    FrameBuffer m_frame_buffer;
};