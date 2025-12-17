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

/** 
 * \brief  Ui Section inside a UiTab. Contains UiElements. 
 * 
 * Can be moved around inside its parent UiTab, but not outside it.
 * Contains a UiSize that all its UiElements can be synced to if desired.
 */
class UiSection : public UiObject
{
public:

	/**
	 * Construct a UiSection under the tab InParent with the name InName.
	 * UiSections have ShouldSyncWidthAcrossElements enabled by default.
	 * 
	 * \param InName Name of this UiSection.
	 * \param InParent Parent UiTab of this UiSection.
	 */
	UiSection(const std::string& InName, UiTab* InParent);

	/** Refresh references to the underlying data this UiSection manages  */
	virtual void Refresh() override;

	/** Update GUI state */
	virtual void Tick() override;

	/**
	 * Calculate the constrained size of this UiSection,
	 * as well as the constrained size of all child UiElements.
	 */
	virtual void CalculateElementConstrainedSizes();

	/**
	 * Add a new UiElement to this section.
	 * 
	 * \param NewElement Element to add to this section.
	 */
	void AddElement(const std::shared_ptr<UiElement> NewElement);

	/**
	 * Calculate a new Synced size this section and store
	 * the result in SyncedSize. This will be
	 * the summed size of every element that doesn't ignore
	 * size syncing.
	 */
	void CalculateSyncedSize();

	/**
	 * Get the parent UiTab for this UiSection.
	 * 
	 * \return Parent UiTab for this UiSection.
	 */
	UiTab* GetParent();

private:

	/** Size that all child UiElements can be synced to if desired. */
	std::shared_ptr<UiSyncedSize> SyncedSize;

	/** Smart pointer not needed because we don't own this object. */
	UiTab* ParentTab;

	/** Dockspace this section is docked in. This is the SectionDockspace of the parent UiTab. */
	std::shared_ptr<ImGuiWindowClass> SectionDockspace;

	/** All UiElements contained in this section. */
	std::vector<std::shared_ptr<UiElement>> UiElements;

	/** Cached available space in the section, used for calculating constrained sizes. */
	float SpaceAvailable = 0.0f;
};
