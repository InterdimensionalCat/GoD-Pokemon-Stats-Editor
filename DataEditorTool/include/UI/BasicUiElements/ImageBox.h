#pragma once
#include "UI/UiElement.h"

typedef unsigned int GLuint;

class ImageBox : public UiElement
{

public:

	ImageBox(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	void SetTexture(const GLuint InTextureID);

	void SetImageSize(const float SquareImageSize);

	void SetImageSize(const float ImageSizeX, const float ImageSizeY);

	ImVec2 GetImageSize() const;

private:

	/**
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
