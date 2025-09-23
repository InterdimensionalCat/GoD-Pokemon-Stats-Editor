#include "include.h"
#include "UI/BasicUiElements/ImageBox.h"

ImageBox::ImageBox(const std::string& InName, UiSection* InParent) : UiElement(InName, InParent)
{
	// Images will always be a fixed size.
	SetSizeSource(UiSizeSource_Self);
	GetSize().SetSizeRule(UiSizeRule_FixedSize);

	// By default set the image size to 100x100 px
	SetImageSize(100.f);
}

void ImageBox::Tick()
{
	if (bImageLoaded)
	{
		ImGui::Image((void*)(intptr_t)TextureID, GetImageSize());
	}
}

void ImageBox::SetTexture(const GLuint InTextureID)
{
	TextureID = InTextureID;
	bImageLoaded = true;
}

void ImageBox::SetImageSize(const float SquareImageSize)
{
	SetImageSize(SquareImageSize, SquareImageSize);
}

void ImageBox::SetImageSize(const float ImageSizeX, const float ImageSizeY)
{
	ImageSize = ImVec2(ImageSizeX, ImageSizeY);
	GetSize().SetMin(ImageSizeX);
}

ImVec2 ImageBox::GetImageSize() const
{
	return ImageSize;
}