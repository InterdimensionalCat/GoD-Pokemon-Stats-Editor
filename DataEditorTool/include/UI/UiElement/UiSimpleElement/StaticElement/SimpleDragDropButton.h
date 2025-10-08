/*****************************************************************//**
 * \file   SimpleDragDropButton.h
 * \brief  SingleUiElement that manages a DragDropButton component.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiComponent/StaticComponent/DragDropButton.h"

template <typename T>
class DragDropButton;

template <typename T>
/**
 * \brief SingleUiElement that manages a DragDropButton component.
 * 
 * A SimpleDragDropButton is a UiSingleElement that manages a DragDropButton
 * component, allowing the user to initiate drag-and-drop operations
 * with a specified payload. It provides functionality to set the
 * preview text displayed during the drag operation.
 */
class SimpleDragDropButton : public UiSingleElement
{

public:

	/**
	 * Construct a SimpleDragDropButton with the supplied name, parent section,
	 * drag-and-drop payload, and drag-and-drop name.
	 * 
	 * \param InName Name of this SimpleDragDropButton.
	 * \param InParent Parent section of this SimpleDragDropButton.
	 * \param InDragDropPayload The payload to be used during the drag-and-drop operation.
	 * \param InDragDropName The name identifier for the drag-and-drop operation.
	 */
	SimpleDragDropButton
	(
		const std::string& InName,
		UiSection* InParent,
		const T& InDragDropPayload,
		const std::string& InDragDropName
	) :
		UiSingleElement(InName, InParent),
		DragDropButtonComponent(std::make_shared<DragDropButton<T>>(InName, this, InDragDropPayload, InDragDropName))
	{
		SetShouldOverrideSyncedSize(true);
		SetUiComponent(DragDropButtonComponent);
	}

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * Does nothing for a SimpleDragDropButton.
	 */
	virtual void UiComponentUpdated() override
	{
		// Implementation intentionally left blank.
	}

	/**
	 * Set the preview text displayed during the drag-and-drop operation.
	 * 
	 * \param PreviewText The preview text to display while dragging.
	 */
	void SetDragDropPreviewText(const std::string& PreviewText)
	{
		DragDropButtonComponent->SetDragDropPreviewText(PreviewText);
	}

private:

	/* The DragDropButton component managed by this SimpleDragDropButton. */
	std::shared_ptr<DragDropButton<T>> DragDropButtonComponent;
};
