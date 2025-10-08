/*****************************************************************//**
 * \file   Command.h
 * \brief  Class encapsulating an action that can be executed, undone, and redone.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

/**
 * \brief  Class encapsulating an action that can be executed, undone, and redone.
 */
class Command {

public:

	/** Construct a Command. */
	Command() = default;

	/** Execute this command. */
	virtual void Execute() = 0;

	/** Undo this command. */
	virtual void Undo() = 0;

	/** Redo this command. */
	virtual void Redo() = 0;

	/** Get the name of this command. */
	virtual std::string GetName() const = 0;

	/** Get a string representation of the changes this command performs. */
	virtual std::string ToString() const = 0;

};