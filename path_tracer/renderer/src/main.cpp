#include <path_tracer.h>
#include <hittable/sphere.h>

float asp_ratio = 16.f / 9.f;

int frame_width = 400;
int frame_height = static_cast<int>(frame_width / asp_ratio);
FrameBuffer frame_buffer(frame_width, frame_height);

int main()
{	
    auto camera = std::make_shared<Camera>();
    camera->m_position = glm::vec3(0.f);
    camera->m_focal_length = 1.f;
    camera->m_asp = asp_ratio;

    auto world = std::make_shared<HittableList>();

    // world.add(std::make_shared<Sphere>(glm::vec3{0.f, 0.f, -8.f}, 4.f));
    world->add(std::make_shared<Sphere>(glm::vec3{0.f, -501.f, -1.f}, 500.f));
    world->add(std::make_shared<Sphere>(glm::vec3{0.f, 0.f, -3.f}, 1.f));

    PathTracer path_tracer(frame_width, frame_height);
    path_tracer.setCamera(camera);
    path_tracer.setWorld(world);

    if (!path_tracer.init())
        return -1;

    path_tracer.render();

	return 0;
}