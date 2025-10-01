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

class UiTab;
class UiElement;
class UiSyncedSize;

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

	virtual void CalculateElementConstrainedSizes();

	void AddElement(const std::shared_ptr<UiElement> NewElement);

	/**
	 * Calculate a new Synced size this section. This will be
	 * the summed size of every element that doesn't ignore
	 * size syncing.
	 * 
	 * We return a const pointer because this summed size is 
	 * not saved and recalculated every tick.
	 * 
	 * TODO: Currently this is re-calculated every tick,
	 * we could probably calculate size
	 */
	void CalculateSyncedSize() const;

	UiTab* GetParent();

private:

	std::shared_ptr<UiSyncedSize> SyncedSize;

	/** Smart pointer not needed because we don't own this object. */
	UiTab* ParentTab;

	std::shared_ptr<ImGuiWindowClass> SectionDockspace;

	std::vector<std::shared_ptr<UiElement>> UiElements;

};
