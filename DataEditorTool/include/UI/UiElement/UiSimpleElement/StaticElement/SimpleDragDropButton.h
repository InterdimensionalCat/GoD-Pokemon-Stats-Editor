#pragma once
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiComponent/StaticComponent/DragDropButton.h"

template <typename T>
class DragDropButton;

template <typename T>
class SimpleDragDropButton : public UiSingleElement
{

public:

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

	virtual void UiComponentUpdated() override
	{
		// Implementation intentionally left blank.
	}

	void SetDragDropPreviewText(const std::string& PreviewText)
	{
		DragDropButtonComponent->SetDragDropPreviewText(PreviewText);
	}

private:

	std::shared_ptr<DragDropButton<T>> DragDropButtonComponent;
};
