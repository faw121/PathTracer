#include <path_tracer.h>
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
    camera->m_position = glm::vec3(0.f);
    camera->m_focal_length = 1.f;
    camera->m_asp = asp_ratio;
}

void initWorld()
{
    // world.add(std::make_shared<Sphere>(glm::vec3{0.f, 0.f, -8.f}, 4.f));
    world->add(std::make_shared<Sphere>(glm::vec3{0.f, -501.f, -1.f}, 500.f));
    world->add(std::make_shared<Sphere>(glm::vec3{0.f, 0.f, -2.f}, 1.f));
}