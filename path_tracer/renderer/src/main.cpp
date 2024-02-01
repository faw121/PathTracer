#include <memory>
#include <path_tracer.h>
#include <material/diffuse.h>
#include <material/metal.h>
#include <material/dielectric.h>
#include <hittable/sphere.h>

float asp_ratio = 16.f / 9.f;

int frame_width = 400;
int frame_height = static_cast<int>(frame_width / asp_ratio);
FrameBuffer frame_buffer(frame_width, frame_height);

auto camera = std::make_shared<Camera>();

auto world = std::make_shared<HittableList>();

void initCamera();

void initWorld();

int main()
{	
    initCamera();
    initWorld();

    PathTracer path_tracer(frame_width, frame_height);
    path_tracer.setCamera(camera);
    path_tracer.setWorld(world);

    if (!path_tracer.init())
        return -1;

    path_tracer.render();

	return 0;
}

void initCamera()
{
    camera->m_position = glm::vec3{-2.f, 2.f, 2.f};
    camera->lookAt(glm::vec3{0.f, 0.f, -2.f});
    camera->m_focal_length = 0.5f;
    camera->m_asp = asp_ratio;
    camera->m_fov = 30.f;
}

void initWorld()
{
    auto diffuse_grey = std::make_shared<Diffuse>(glm::vec3{0.6f});
    auto diffuse_green = std::make_shared<Diffuse>(glm::vec3{0.19f, 0.73f, 0.69f});
    auto metal_gold = std::make_shared<Metal>(glm::vec3{0.8f, 0.6f, 0.2f}, 0.5f);
    auto metal_grey = std::make_shared<Metal>(glm::vec3{0.8f, 0.8f, 0.8f}, 0.3f);
    auto dielectric = std::make_shared<Dielectric>(1.5f);

    auto sphere_ground = std::make_shared<Sphere>(glm::vec3{0.f, -801.f, -2.f}, 800.f, diffuse_grey);
    auto ball_middle = std::make_shared<Sphere>(glm::vec3{0.f, 0.f, -2.f}, 1.f, diffuse_green);
    auto ball_left = std::make_shared<Sphere>(glm::vec3{-2.f, 0.f, -2.f}, 1.f, dielectric);
    auto ball_inside = std::make_shared<Sphere>(glm::vec3{-2.f, 0.f, -2.f}, -0.8f, dielectric);
    auto ball_right = std::make_shared<Sphere>(glm::vec3{2.f, 0.f, -2.f}, 1.f, metal_gold);

    world->add(sphere_ground);
    world->add(ball_middle);
    world->add(ball_left);
    world->add(ball_right);
    world->add(ball_inside);
}