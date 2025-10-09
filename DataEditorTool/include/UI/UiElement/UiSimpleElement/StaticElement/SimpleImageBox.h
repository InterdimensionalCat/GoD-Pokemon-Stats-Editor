/*****************************************************************//**
 * \file   SimpleImageBox.h
 * \brief  UiSingleElement that manages an ImageBox component.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiElement/UiSingleElement.h"

class ImageBox;

/**
 * \brief  UiSingleElement that manages an ImageBox component.
 */
class SimpleImageBox : public UiSingleElement
{

	typedef unsigned int GLuint;

public:

	/**
	 * Construct a SimpleImageBox with the supplied name and parent section.
	 * 
	 * \param InName Name of this SimpleImageBox.
	 * \param InParent Parent section of this SimpleImageBox.
	 */
	SimpleImageBox(const std::string& InName, UiSection* InParent);

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * Does nothing for a SimpleImageBox.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set the OpenGL texture ID to display in this ImageBox.
	 * 
	 * \param InTextureID OpenGL texture ID to display.
	 */
	void SetTexture(const GLuint InTextureID);

	/**
	 * Set the size of the image to display in this ImageBox.
	 * 
	 * This sets both the X and Y size to the same value.
	 * 
	 * \param SquareImageSize Size to set both X and Y to.
	 */
	void SetImageSize(const float SquareImageSize);

	/**
	 * Set the size of the image to display in this ImageBox.
	 * 
	 * This sets the X and Y size independently.
	 * 
	 * \param ImageSizeX Size to set the X dimension to.
	 * \param ImageSizeY Size to set the Y dimension to.
	 */
	void SetImageSize(const float ImageSizeX, const float ImageSizeY);

	/**
	 * Get the size of the image being displayed in this ImageBox.
	 * 
	 * \return Size of the image being displayed in this ImageBox.
	 */
	ImVec2 GetImageSize() const;

private:

	/* The ImageBox component managed by this SimpleImageBox. */
	std::shared_ptr<ImageBox> ImageBoxComponent;

};
