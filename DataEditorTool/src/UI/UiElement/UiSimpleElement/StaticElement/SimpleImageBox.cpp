#include "include.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleImageBox.h"
#include "UI/UiComponent/StaticComponent/ImageBox.h"

typedef unsigned int GLuint;

SimpleImageBox::SimpleImageBox(const std::string& InName, UiSection* InParent)
: UiSingleElement(InName, InParent),
  ImageBoxComponent(std::make_shared<ImageBox>(InName, this))
{
	SetShouldOverrideSyncedSize(true);
	SetUiComponent(ImageBoxComponent);
}

void SimpleImageBox::UiComponentUpdated()
{
	// Implementation intentionally left blank.
}

void SimpleImageBox::SetTexture(const GLuint InTextureID)
{
	ImageBoxComponent->SetTexture(InTextureID);
}

void SimpleImageBox::SetImageSize(const float SquareImageSize)
{
	ImageBoxComponent->SetImageSize(SquareImageSize, SquareImageSize);
}

void SimpleImageBox::SetImageSize(const float ImageSizeX, const float ImageSizeY)
{
	ImageBoxComponent->SetImageSize(ImageSizeX, ImageSizeY);
}

ImVec2 SimpleImageBox::GetImageSize() const
{
	return ImageBoxComponent->GetImageSize();
}