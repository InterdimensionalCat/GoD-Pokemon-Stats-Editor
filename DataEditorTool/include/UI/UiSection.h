/*****************************************************************//**
 * \file   UiSection.h
 * \brief  Ui Section inside a UiTab. Contains UiElements. 
 * Can be moved around inside its parent UiTab, but not outside it.
 * Contains a UiSize that all its UiElements can be synced to if desired.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "UI/UiObject.h"
#include "UI/UiSize.h"

class UiTab;
class UiElement;
class UiCSVElement;

// TODO: UiSections have 3 types of UiElements:
// UiCSVElement: manages CSV data
// UiElement: Needed UI that does not manage CSV data
// UiSubsection: Is a child window containing
// Multiple other UI elements

/**
 * Ui section inside a window. Contains UiElements
 * May contain 1 or more subsections.
 * Can be moved around inside their parent window
 */
class UiSection : public UiObject
{
public:

	/**
	 * Construct a UiSection under the tab InParent with the name InName.
	 * UiSections have ShouldSyncWidthAcrossElements enabled by default.
	 */
	UiSection(const std::string& InName, UiTab* InParent);

	virtual void Refresh() override;

	virtual void Tick() override;

	void AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement);
	void AddElement(const std::shared_ptr<UiElement> NewElement);

	void SetShouldSyncWidthAcrossElements(const bool ShouldSync);

	void CalcNumItemsOnNextLine(const uint32_t ItemIndex);

	bool ShouldSyncWidthAcrossElements();

	/**
	 * UiSections usually will want to be at least long enough
	 * to display their longest element or subsection correctly.
	 */
	virtual float GetMinNeededWidth();

	/**
	 * Usually, the max allowed will be the minimum max allowed of
	 * this UiSection's elements.
	 */
	virtual float GetMaxAllowedWidth();

	/** Get the label size of this UiSection's largest element label. */
	virtual float GetElementsMaxLabelSize();

	/**
	 * This is const because this will get reset every tick.
	 * If element syncing is turned on set the Min/Max of each element
	 */
	const UiSize& GetSyncedSize() const;

	uint32_t GetNumItemsThisLine() const;

	UiTab* GetParent();

private:

	/** Smart pointer not needed because we don't own this object. */
	UiTab* ParentTab;

	std::shared_ptr<ImGuiWindowClass> SectionDockspace;

	std::vector<std::shared_ptr<UiElement>> UiElements;

	bool bShouldSyncWidthAcrossElements;

	UiSize SyncedSize;

	uint32_t NumItemsThisLine = 1;
};
