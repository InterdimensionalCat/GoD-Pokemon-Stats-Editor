/*****************************************************************//**
 * \file   UiChildWindow.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiSyncedSize;

 /**
  * \brief
  *
  * UiChildWindow is a UiMultiElement that represents a child window
  * in the ImGui interface. Child windows are used to create
  * scrollable regions within a parent window.
  */
class UiChildWindow : public UiMultiElement
{
public:
	/**
	 * Construct a UiChildWindow with the supplied name and parent section.
	 *
	 * \param InName Name of this UiChildWindow.
	 * \param InParent Parent section of this UiChildWindow.
	 */
	UiChildWindow(const std::string& InName, UiSection* InParent);

	/**
	 * Tick this UiChildWindow, rendering the child window
	 * and ticking all child UiElements within it.
	 */
	virtual void Tick() override;

	void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	) override;

	virtual void SetSameLine(const bool bInSameLine) override;
	virtual void SetSameLine(const float OffsetFromStart) override;

	void CalculateSyncedSize();

	void SetNumLines(const int32_t InNumLines);

	void SetIsFixedSize(const bool bInIsFixedSize);

	void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	/**
	 * Get the size constraints for this UiChildWindow. This
	 * is always no size constraints
	 *
	 * \return The size constraints for this UiChildWindow.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

	int32_t GetNumLines() const;

private:

	std::shared_ptr<UiSyncedSize> SyncedSize;

	bool bIsSameLine = false;
	float SameLineOffsetFromStart = 0.f;

	int32_t NumLines = 0;
};
