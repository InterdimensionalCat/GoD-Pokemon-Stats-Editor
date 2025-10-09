/*****************************************************************//**
 * \file   UiSingleElement.h
 * \brief  UiElement that manages and displays a single UiComponent
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiElement.h"

class UiComponent;

/**
 * \brief UiElement that manages and displays a single UiComponent
 * 
 * A UiSingleElement contains and displays a single UiComponent,
 * such as an IntBox or ComboBox. It handles displaying the component
 * and reacting to any updates in the component via
 * the pure virtual UiComponentUpdated function.
 */
class UiSingleElement : public UiElement
{

public:

	/**
	 * Construct a UiSingleElement with the supplied name and parent section.
	 * 
	 * \param InName Name of this UiSingleElement.
	 * \param InParent Parent section of this UiSingleElement.
	 */
	UiSingleElement(
		const std::string& InName,
		UiSection* InParent
	);

	/**
	 * Tick the UiComponent managed by this UiSingleElement.
	 */
	virtual void Tick() override;

	/**
	 * Pure virtual function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 * 
	 * This should be implemented by subclasses to react to updates
	 * in the UiComponent, such as updating the underlying data
	 * the component manages.
	 */
	virtual void UiComponentUpdated() = 0;

	/**
	 * Get the size constraints for this UiSingleElement.
	 * This will be the size constraints of its UiComponent.
	 * 
	 * \return The size constraints for this UiSingleElement.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

	/**
	 * Get the UiComponent managed by this UiSingleElement.
	 * 
	 * \return The UiComponent managed by this UiSingleElement.
	 */
	std::shared_ptr<const UiComponent> GetUiComponent() const;

	/**
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section.
	 * 
	 * \param bInSameLine True if this element should be displayed on the same line as the previous element.
	 */
	virtual void SetSameLine(const bool bInSameLine) override;

	/**
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section,
	 * with an offset from the start of the line.
	 * 
	 * \param OffsetFromStart The offset from the start of the line to display this element at.
	 */
	virtual void SetSameLine(const float OffsetFromStart) override;

	/**
	 * Set whether or not this element should be disabled (grayed out).
	 * 
	 * \param bInDisabled True if this element should be disabled.
	 */
	virtual void SetDisabled(const bool bInDisabled) override;

	/**
	 * Set whether or not the UiComponent managed by this UiSingleElement
	 * should be a fixed size.
	 * 
	 * \param bInIsFixedSize True if the UiComponent should be a fixed size.
	 */
	void SetIsFixedSize(const bool bInIsFixedSize);

protected:

	/**
	 * Set the UiComponent managed by this UiSingleElement.
	 * 
	 * \param NewComponent The new UiComponent to manage.
	 */
	void SetUiComponent(std::shared_ptr<UiComponent> NewComponent);

	/* The UiComponent managed by this UiSingleElement. */
	std::shared_ptr<UiComponent> Component;
};