/*****************************************************************//**
 * \file   ImageBox.h
 * \brief  UiComponent that displays an image/texture.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that displays an image/texture.
 */
class ImageBox : public UiComponent
{

	typedef unsigned int GLuint;

public:

	/**
	 * Construct an ImageBox with the supplied name and parent element.
	 * This ImageBox will have no label by default.
	 * 
	 * \param InName Name of this ImageBox.
	 * \param InParent Parent UiSingleElement of this ImageBox.
	 */
	ImageBox(const std::string& InName, UiSingleElement* InParent);

	/**
	 * Display this ImageBox using ImGui::Image.
	 * 
	 * If no texture is loaded, nothing will be displayed.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Set the OpenGL texture ID to display in this ImageBox.
	 * 
	 * \param InTextureID The OpenGL texture ID to display in this ImageBox.
	 */
	void SetTexture(const GLuint InTextureID);

	/**
	 * Set the size to render this image at, using the same value for both width and height.
	 * 
	 * \param SquareImageSize The size to render this image at, for both width and height.
	 */
	void SetImageSize(const float SquareImageSize);

	/**
	 * Set the size to render this image at, using separate values for width and height.
	 * 
	 * \param ImageSizeX The width to render this image at.
	 * \param ImageSizeY The height to render this image at.
	 */
	void SetImageSize(const float ImageSizeX, const float ImageSizeY);

	/**
	 * Get the size this image is being rendered at.
	 * 
	 * \return The size this image is being rendered at.
	 */
	ImVec2 GetImageSize() const;

	/**
	 * Calculate the internal space required by this ImageBox,
	 * excluding label size.
	 * 
	 * \return The internal space required by this ImageBox, excluding label size.
	 */
	float CalculateInternalSpace() const override;

private:

	/**
	 * The Texture ID of the image to display.
	 * 
	 * 0 is never a valid texture, so this indicates
	 * that no texture is loaded.
	 */
	GLuint TextureID = 0;

	/** The size to render this image at */
	ImVec2 ImageSize;

	/**
	 * Have we ever loaded an image? An image
	 * must be loaded for this element to be displayed.
	 */
	bool bImageLoaded = false;

};
