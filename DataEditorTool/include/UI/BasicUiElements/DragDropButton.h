#pragma once
#include "include.h"
#include "UI/BasicUiElements/DragDropButton.h"

#pragma once
#include "UI/UiElement.h"

template <typename T>
class DragDropButton : public UiElement
{

public:

	DragDropButton
	(
		const std::string& InName,
		UiSection* InParent,
		const T& InDragDropPayload,
		const std::string& InDragDropName
	) :
		UiElement(InName, InParent),
		DragDropPreviewText(""),
		DragDropName(InDragDropName),
		DragDropPayload(InDragDropPayload)
	{
		GetSize().SetSizeRule(UiSizeRule_FixedSize);
		GetSize().SetMinFromStringLength(1);
	}

	virtual void Tick() override
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

private:

	std::string DragDropPreviewText = "";

	std::string DragDropName = "";

	T DragDropPayload;

};
