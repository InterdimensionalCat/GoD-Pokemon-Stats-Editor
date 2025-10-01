#include "include.h"
#include "UI/UiComponent/StaticComponent/ImageBox.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

ImageBox::ImageBox(const std::string& InName, UiSingleElement* InParent) : UiComponent(InName, InParent)
{
	// Images will always be a fixed size.
	ComponentSize->SetIsFixedSize(true);

	// By default set the image size to 100x100 px
	SetImageSize(100.f);
}

void ImageBox::DisplayComponent()
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
	ComponentSize->SetMin(UiSizeBound("", CalculateInternalSpace(), ImageSizeX));
}

ImVec2 ImageBox::GetImageSize() const
{
	return ImageSize;
}

bool ImageBox::HasLabel() const
{
	// Images never have a label.
	return false;
}

float ImageBox::CalculateInternalSpace() const
{
	return 0.f;
}