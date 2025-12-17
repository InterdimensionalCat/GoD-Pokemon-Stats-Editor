/*****************************************************************//**
 * \file   UiGroup.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiSyncedSize;

class UiGroup : public UiMultiElement
{
public:
	/**
	 * Construct a UiGroup with the supplied name and parent section.
	 *
	 * \param InName Name of this UiGroup.
	 * \param InParent Parent section of this UiGroup.
	 */
	UiGroup(const std::string& InName, UiSection* InParent);

	/**
	 * Tick this UiGroup,ticking all child 
	 * UiElements within it.
	 */
	virtual void Tick() override;

	void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	) override;

	virtual void SetSameLine(const bool bInSameLine) override;
	virtual void SetSameLine(const float OffsetFromStart) override;

	void CalculateSyncedSize();

	void SetIsFixedSize(const bool bInIsFixedSize);

	void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	/**
	 * Get the size constraints for this UiChildWindow. This
	 * is always no size constraints
	 *
	 * \return The size constraints for this UiChildWindow.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

private:

	std::shared_ptr<UiSyncedSize> SyncedSize;

	bool bIsSameLine = false;
	float SameLineOffsetFromStart = 0.f;

};
