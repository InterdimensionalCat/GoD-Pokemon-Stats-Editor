/*****************************************************************//**
 * \file   UiElement.h
 * \brief Lowest level Ui object. Manages and displays 1 UI element.
 * Such as a button or text entry box. Ui elements in ImGui always 
 * have a label along with a UI element. both need to be used in width calcluations
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "UI/UiObject.h"
#include "UI/UiSize.h"

class UiSection;
class UiSubsection;

enum class UiSizeSource : uint8_t
{
	/** Inherit from parent UiSection if enabled, use own min/max size constraints if not. */
	UiSizeSource_Parent,

	/** Ignore parent UiSection sizing even if its enabled, and just use own min/max size constraints. */
	UiSizeSource_Self
};

using enum UiSizeSource;

/**
 * Lowest level Ui object. Manages and displays 1 UI element.
 * Such as a button or text entry box.
 *
 * Ui elements in ImGui always have a label along with a UI element.
 * both need to be used in width calcluations
 */
class UiElement : public UiObject
{
public:

	UiElement(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	/**
	 * Sets the ImGui next element width to the appropreate 
	 * value for this UiElement based on its UiSizeSource.
	 */
	virtual void PushConstrainedElementSize();

	/**
	 * Pops the ImGui next element width set by 
	 * PushConstrainedElementSize().
	 */
	virtual void PopConstrainedElementSize();

	void SetSameLine(const bool IsSameLine);
	void SetDisabled(const bool InIsDisabled);
	void SetSizeSource(const UiSizeSource InSizeSource);

	bool IsSameLine() const;
	bool IsDisabled() const;
	virtual float GetLabelSize();
	UiSize& GetSize();
	const UiSize& GetSize() const;
	UiSizeSource GetSizeSource() const;

protected:

	UiSection* ParentSection;

private:

	UiSizeSource SizeSource;

	UiSize ElementSize;

	bool bIsSameLine = false;

	bool bIsDisabled = false;

};
