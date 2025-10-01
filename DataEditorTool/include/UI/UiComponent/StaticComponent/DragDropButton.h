#pragma once
#include "include.h"
#include "UI/UiComponent/UiComponent.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"


template <typename T>
class DragDropButton : public UiComponent
{

public:

	DragDropButton
	(
		const std::string& InName,
		UiSingleElement* InParent,
		const T& InDragDropPayload,
		const std::string& InDragDropName
	) :
		UiElement(InName, InParent),
		DragDropPreviewText(""),
		DragDropName(InDragDropName),
		DragDropPayload(InDragDropPayload)
	{
		ComponentSize.SetIsFixedSize(true);
		SetMinContentSizeFromStringLength(1);
	}

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

	void SetDragDropPreviewText(const std::string& PreviewText)
	{
		DragDropPreviewText = PreviewText;
	}

	virtual float CalculateInternalSpace() const override
	{
		float InternalSize = 0.f;
		auto& Style = ImGui::GetStyle();

		// Unlike square buttons such as CheckBoxes, regular buttons
		// do use FramePadding.x on both sides, but thats it.
		InternalSize += Style.FramePadding.x * 2;

		return InternalSize;
	}

	virtual bool HasLabel() const override
	{
		// DragDropButtons never have a label.
		return false;
	}

private:

	std::string DragDropPreviewText = "";

	std::string DragDropName = "";

	T DragDropPayload;

};
