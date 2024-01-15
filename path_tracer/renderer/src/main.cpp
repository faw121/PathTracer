#include <algorithm>
#include <array>
#include<iostream>
#include <format>
#include <fstream>
#include <iterator>
#include <stdint.h>
#include <vector>

#include <basic/frame_buffer.h>


#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <3rdParty/stb_image_write.h>

int main()
{	
	int image_width = 256;
    int image_height = 256;

	FrameBuffer frame_buffer(image_width, image_height);

	for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0;

            float ir = static_cast<float>(255.999 * r);
            float ig = static_cast<float>(255.999 * g);
            float ib = static_cast<float>(255.999 * b);

            // frame_buffer
			frame_buffer.set(j, i, std::array<float, 4>{ir, ig, ib, 255.f});
        }
    }

    std::clog << "\rDone.                 \n";

	stbi_write_bmp("out.bmp", image_width, image_height, 4, frame_buffer.data());

	return 0;
}