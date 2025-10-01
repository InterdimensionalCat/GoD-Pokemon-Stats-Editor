#pragma once
#include "UI/UiComponent/UiComponent.h"

class ImageBox : public UiComponent
{

	typedef unsigned int GLuint;

public:

	ImageBox(const std::string& InName, UiSingleElement* InParent);

	virtual void DisplayComponent() override;

	void SetTexture(const GLuint InTextureID);

	void SetImageSize(const float SquareImageSize);

	void SetImageSize(const float ImageSizeX, const float ImageSizeY);

	ImVec2 GetImageSize() const;

	virtual bool HasLabel() const override;

	float CalculateInternalSpace() const override;

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
