/*****************************************************************//**
 * \file   UiObject.h
 * \brief  Base class for all UI classes
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

/**
 * \brief  Base class for all UI classes
 * 
 * Contains a common interface for tick-able UI classes,
 * as well as the name of the UI object. This name should
 * generally be unique among sibling UI objects, but serves
 * different purposes depending on the type of UI object.
*/
class UiObject
{
public:

	/**
	 * Construct a UiObject with the supplied name and parent.
	 * 
	 * The parent may be nullptr if this is a root UI object.
	 * TODO: having a parent pointer at all may not be needed,
	 * as each UiObject implementation that cares about its
	 * parent stores a typed pointer so we don't have to
	 * dynamic cast all the time.
	 * 
	 * \param InName Name of this UiObject.
	 * \param InParent Parent of this UiObject, may be nullptr.
	 */
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
	 * 
	 * \return Name of this UiObject.
	 * \note return type changed to const ref to avoid copies. Due to
	 * the number of times this gets called in a frame we spend a non-trivial
	 * amount of time copying strings otherwise.
	 */
	const std::string& GetName() const;

	/**
	 * Return the name of this UiObject, but
	 * add "##" to the beginning
	 * it if it doesn't already have 
	 * "##" somewhere in the name.
	 * 
	 * \return Name of this UiObject with "##" perpended if not already present.
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