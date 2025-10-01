/*****************************************************************//**
 * \file   UiObject.h
 * \brief  Base class for all UI classes
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

/**
* All UI classes inherit from UiObject.
*/
class UiObject
{
public:

	// TODO: pass in initial position?
	UiObject(const std::string& InName, UiObject* InParent = nullptr);

	/** Refresh references to the underlying data this UiObject manages  */
	virtual void Refresh();

	/** Update GUI state */
	virtual void Tick();

	/**
	 * Return the name of this UiObject.
	 * 
	 * Name has several uses depending on which type of UI element this is.
	 * UiTab: Name of the window tab.
	 * UiSection: Name of the section tab.
	 * UiSubsection: the header text at the top of the subsection.
	 * UiElement: the label name.
	 */
	std::string GetName() const;

	/**
	 * Return the name of this UiObject, but
	 * add "##" to the beginning
	 * it if it doesn't already have 
	 * "##" somewhere in the name.
	 */
	std::string GetInvisibleName() const;

private:
	/*
	 * Name has several uses depending on which type of UI element this is.
	 * UiTab: Name of the window tab.
	 * UiSection: Name of the section tab.
	 * UiElement: LabelName+element type for single elements,
	 * Parent name for multi/parent elements.
	 * UiComponent: the label name.
	 */
	std::string Name;

	/**
	 * Raw pointer is used here because the child does not own the parent,
	 * So it does not need to manage its lifetime. Additionally this circumvents
	 * the need to make all UI classes inherit from shared_from_this
	 * 
	 * TODO: this pointer may no longer be needed, as each UiObject implementation
	 * stores a typed pointer to its parent.
	 */
	UiObject* Parent;
};