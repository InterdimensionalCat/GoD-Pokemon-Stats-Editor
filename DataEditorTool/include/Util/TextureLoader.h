/*****************************************************************//**
 * \file   TextureLoader.h
 * \brief  Helper functions and classes for loading textures and images from files or memory.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

typedef unsigned int GLuint;
struct GLFWimage;

/**
 * \brief  Helper class that contains both a GLFWimage and its associated pixel data.
 * 
 * The pixel data must remain valid for the lifetime of the GLFWimage,
 * so we store it as an unaccessible private member for the lifetime of this class.
 */
class ImageAndPixelData
{

public:

	/**
	 * Construct an ImageAndPixelData from the supplied GLFWimage and pixel data.
	 * The pixel data must remain valid for the lifetime of the GLFWimage,
	 * so we store it as an unaccessible private member for the lifetime of this class.
	 * 
	 * \param InImageData The GLFWimage to store.
	 * \param InPixelData The pixel data associated with the GLFWimage.
	 */
	ImageAndPixelData(
		std::shared_ptr<GLFWimage> InImageData,
		unsigned char* InPixelData
	);

	/** The loaded GLFWimage data */
	std::shared_ptr<GLFWimage> ImageData;

private:

	/** The pixel data associated with the GLFWimage. This must remain valid for the lifetime of the GLFWimage. */
	std::shared_ptr<unsigned char[]> PixelData;
};


/**
 * \brief Load a texture from memory data.
 * 
 * \param data Pointer to the memory data to load the texture from.
 * \param data_size Size of the memory data in bytes.
 * \param out_texture Pointer to a GLuint to store the loaded texture ID.
 * \param out_width Pointer to an int to store the width of the loaded texture.
 * \param out_height Pointer to an int to store the height of the loaded texture.
 * \return True if the texture was loaded successfully, false otherwise.
 */
bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height);


/**
 * \brief Load an image from memory data.
 * 
 * The returned ImageAndPixelData contains both the loaded GLFWimage
 * and its associated pixel data. The pixel data must remain valid
 * for the lifetime of the GLFWimage, so we store it as an unaccessible
 * private member for the lifetime of the ImageAndPixelData class.
 * 
 * \param data Pointer to the memory data to load the image from.
 * \param data_size Size of the memory data in bytes.
 * \return A shared pointer to an ImageAndPixelData containing the loaded image and its pixel data,
 * or nullptr if the image could not be loaded.
 */
std::shared_ptr<ImageAndPixelData> LoadImageFromMemory(const void* data, size_t data_size);


/**
 * \brief Load a texture from a file.
 * 
 * \param file_name The path to the file to load the texture from.
 * \param out_texture Pointer to a GLuint to store the loaded texture ID.
 * \param out_width Pointer to an int to store the width of the loaded texture.
 * \param out_height Pointer to an int to store the height of the loaded texture.
 * \return True if the texture was loaded successfully, false otherwise.
 */
bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height);


/**
 * \brief Load an image from a file.
 * 
 * The returned ImageAndPixelData contains both the loaded GLFWimage
 * and its associated pixel data. The pixel data must remain valid
 * for the lifetime of the GLFWimage, so we store it as an unaccessible
 * private member for the lifetime of the ImageAndPixelData class.
 * 
 * \param file_name The path to the file to load the image from.
 * \return A shared pointer to an ImageAndPixelData containing the loaded image and its pixel data,
 * or nullptr if the image could not be loaded.
 */
std::shared_ptr<ImageAndPixelData> LoadImageFromFile(const char* file_name);