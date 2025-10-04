#pragma once
#include "UI/UiElement/UiSingleElement.h"

class ImageBox;


class SimpleImageBox : public UiSingleElement
{

	typedef unsigned int GLuint;

public:

	SimpleImageBox(const std::string& InName, UiSection* InParent);

	virtual void UiComponentUpdated() override;

	void SetTexture(const GLuint InTextureID);

	void SetImageSize(const float SquareImageSize);

	void SetImageSize(const float ImageSizeX, const float ImageSizeY);

	ImVec2 GetImageSize() const;

private:

	std::shared_ptr<ImageBox> ImageBoxComponent;

};
