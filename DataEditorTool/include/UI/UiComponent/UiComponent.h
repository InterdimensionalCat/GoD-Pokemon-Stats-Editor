#pragma once
#include "UI/UiObject.h"

class UiSingleElement;
class UiSize;

/**
 * Lowest level Ui object. Manages and displays 1 piece of ImGui UI.
 * Such as a button or text entry box.
 *
 * Ui elements in ImGui always have a label along with a UI element.
 * both need to be used in width calculations
 */
class UiComponent : public UiObject
{
public:

	UiComponent(
		const std::string& InName,
		UiSingleElement* InParent,
		const bool InHasLabel
	);

	UiComponent(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Prepare this UiComponent for display by setting state such
	 * as disabled and same line, then call DisplayComponent() to
	 * render this element. Any Component specific display code
	 * should be overridden in DisplayComponent().
	 */
	void Tick();

	/**
	 * Display this UiComponent using whatever ImGui UI
	 * this UiComponent implements.
	 */
	virtual void DisplayComponent();

	void ComponentUpdated();

	void SetSameLine(const bool IsSameLine);
	void SetSameLine(const float OffsetFromStart);
	void SetDisabled(const bool InIsDisabled);

	void SetMinContentSizeFromString(const std::string& NewMinString);
	void SetMaxContentSizeFromString(const std::string& NewMaxString);

	void SetMinContentSizeFromStringLength(const uint32_t NewMinStringLength);
	void SetMaxContentSizeFromStringLength(const uint32_t NewMaxStringLength);

	std::shared_ptr<UiSize> GetSizeConstraints();

	std::shared_ptr<const UiSize> GetSizeConstraints() const;

	bool IsSameLine() const;
	bool IsDisabled() const;

	/**
	 * Return the label size of this UiComponent.
	 * This is virtual because some elements never
	 * have a label, even if their name has a label size.
	 */
	 // virtual float GetLabelSize() const;
	bool HasLabel() const;

	/**
	 * Calculate the internal space this UiComponent,
	 * not including the InnerItemSpacing between
	 * the label and the element itself.
	 */
	virtual float CalculateInternalSpace() const;

protected:

	UiSingleElement* ParentElement;

	// TODO: Have a MultiUiSize that calculates size constraints
	// using multiple UiSizes, such as summing the bounds of all
	// contained UiSizes, or calculating the highest min and lowest
	// max of all contained UiSizes.
	std::shared_ptr<UiSize> ComponentSize;


private:

	bool bHasLabel = true;

	bool bIsSameLine = false;

	float SameLineOffsetFromStart = 0.f;

	bool bIsDisabled = false;

};