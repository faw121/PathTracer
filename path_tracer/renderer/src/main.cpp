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

void initWorldRand();

void initConellBox();

int main()
{	
    initCamera();
    // initWorld();
    initWorldRand();

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
    camera->m_position = glm::vec3{-2.f, 2.f, 0.f};
    camera->lookAt(glm::vec3{0.f, 0.f, -2.f});
    camera->m_focal_length = 3.2f;
    camera->m_asp = asp_ratio;
    camera->m_fov = 60.f;
    camera->m_defocus_angle = 10.f;
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

void initWorldRand()
{
    auto diffuse_grey = std::make_shared<Diffuse>(glm::vec3{0.5f});
    auto sphere_ground = std::make_shared<Sphere>(glm::vec3{0.f, -1000.f, 0.f}, 1000.f, diffuse_grey);
    world->add(sphere_ground);

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float rand_material = randomFloat();
            auto center = glm::vec3{a + 0.9f * randomFloat(), 0.2f, b + 0.9f * randomFloat()};

            if (glm::length(center - glm::vec3{4.f, 0.2f, 0.f}) > 0.9f) {
                std::shared_ptr<Material> material;

                if (rand_material < 0.8f) {
                    auto albedo = randomVec3();
                    material = std::make_shared<Diffuse>(albedo);
                    world->add(std::make_shared<Sphere>(center, 0.2f, material));
                }
                else if (rand_material < 0.95) {
                    auto albedo = randomVec3(0.5f, 1.f);
                    auto fuzz = randomFloat(0.f, 0.5f);
                    material = std::make_shared<Metal>(albedo, fuzz);
                    world->add(std::make_shared<Sphere>(center, 0.2f, material));
                }
                else {
                    material = std::make_shared<Dielectric>(1.5f);
                    world->add(std::make_shared<Sphere>(center, 0.2f, material));
                }
            }
        }
    }

    auto dielectric = std::make_shared<Dielectric>(1.5f);
    world->add(std::make_shared<Sphere>(glm::vec3{0.f, 1.f, 0.f}, 1.f, dielectric));

    auto diffuse = std::make_shared<Diffuse>(glm::vec3{0.4f, 0.2f, 0.1f});
    world->add(std::make_shared<Sphere>(glm::vec3{-4.f, 1.f, 0.f}, 1.f, diffuse));

    auto metal = std::make_shared<Metal>(glm::vec3{0.7f, 0.6f, 0.5f}, 0.f);
    world->add(std::make_shared<Sphere>(glm::vec3{4.f, 1.f, 0.f}, 1.f, metal));

    camera->m_position = glm::vec3{13.f, 2.f, 3.f};
    camera->m_fov = 20.f;
    camera->lookAt(glm::vec3{0.f});
    camera->m_defocus_angle = 0.6f;
    camera->m_focal_length = 10.f;
}

