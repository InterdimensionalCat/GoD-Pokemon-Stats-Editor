#pragma once

class Command {

public:

	Command() = default;

	virtual void Execute() = 0;

	virtual void Undo() = 0;

	virtual void Redo() = 0;

	virtual std::string GetName() const = 0;

	virtual std::string ToString() const = 0;

};