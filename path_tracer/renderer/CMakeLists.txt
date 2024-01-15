set(TARGET_NAME path_tracer)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp)

add_executable(${TARGET_NAME} ${srcs})

target_include_directories(${TARGET_NAME} PUBLIC include)
target_link_libraries(${TARGET_NAME} PUBLIC glm)