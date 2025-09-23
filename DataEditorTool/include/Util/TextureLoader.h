#pragma once

typedef unsigned int GLuint;
struct GLFWimage;

class ImageAndPixelData
{

public:

	ImageAndPixelData(
		std::shared_ptr<GLFWimage> InImageData,
		unsigned char* InPixelData
	);

	std::shared_ptr<GLFWimage> ImageData;

private:

	std::shared_ptr<unsigned char[]> PixelData;
};

bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height);

std::shared_ptr<ImageAndPixelData> LoadImageFromMemory(const void* data, size_t data_size);

bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height);

std::shared_ptr<ImageAndPixelData> LoadImageFromFile(const char* file_name);