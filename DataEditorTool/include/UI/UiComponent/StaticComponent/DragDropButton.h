/*****************************************************************//**
 * \file   DragDropButton.h
 * \brief  UiComponent that displays a button which can be dragged.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "include.h"
#include "UI/UiComponent/UiComponent.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"


template <typename T>
/**
 * \brief  UiComponent that displays a button which can be dragged.
 * 
 * The template type T is the type of the payload that will be sent when
 * a DragDropTarget receives the payload from this DragDropButton.
 */
class DragDropButton : public UiComponent
{

public:

	/**
	 * \brief Construct a DragDropButton with the supplied name, parent element,
	 * drag drop payload, and drag drop name.
	 * 
	 * \param InName Name of this DragDropButton.
	 * \param InParent Parent UiSingleElement of this DragDropButton.
	 * \param InDragDropPayload The payload to be sent when this button is dragged.
	 * \param InDragDropName The name of the drag drop payload.
	 */
	DragDropButton
	(
		const std::string& InName,
		UiSingleElement* InParent,
		const T& InDragDropPayload,
		const std::string& InDragDropName
	) :
		UiComponent(InName, InParent, false),
		DragDropPreviewText(""),
		DragDropName(InDragDropName),
		DragDropPayload(InDragDropPayload)
	{
		ComponentSize->SetIsFixedSize(true);
		SetMinContentSizeFromStringLength(1);
	}

	/**
	 * \brief Display this DragDropButton using ImGui.
	 * 
	 * This will display a button with the name of this DragDropButton,
	 * and allow it to be dragged. When dragged, it will send the
	 * DragDropPayload to any DragDropTarget that accepts it.
	 */
	virtual void DisplayComponent() override
	{
		auto DragDropButtonName = std::format("↕{}", GetInvisibleName());
		ImGui::Button(DragDropButtonName.c_str());

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			// Set payload the DragDropPayload.
			ImGui::SetDragDropPayload(DragDropName.c_str(), &DragDropPayload, sizeof(T));

			// Display preview text.
			ImGui::Text(DragDropPreviewText.c_str());
			ImGui::EndDragDropSource();
		}
	}

	/**
	 * \brief Set the text to be displayed when this DragDropButton is dragged.
	 * 
	 * \param PreviewText The text to be displayed when this DragDropButton is dragged.
	 */
	void SetDragDropPreviewText(const std::string& PreviewText)
	{
		DragDropPreviewText = PreviewText;
	}

	/**
	 * \brief Calculate the internal space required by this DragDropButton.
	 * 
	 * \return The internal space required by this DragDropButton.
	 */
	virtual float CalculateInternalSpace() const override
	{
		float InternalSize = 0.f;
		auto& Style = ImGui::GetStyle();

		// Unlike square buttons such as CheckBoxes, regular buttons
		// do use FramePadding.x on both sides, but thats it.
		InternalSize += Style.FramePadding.x * 2;

		return InternalSize;
	}

private:

	/** Text to be displayed when this button is being dragged. */
	std::string DragDropPreviewText = "";

	/** Name of the drag drop payload. */
	std::string DragDropName = "";

	/** Payload to be sent when this button is dragged. */
	T DragDropPayload;

};
