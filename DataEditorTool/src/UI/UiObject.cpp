#include "include.h"
#include "UI/UiObject.h"

UiObject::UiObject(const std::string& InName, UiObject* InParent) :
	Name(InName), 
	Parent(InParent) {}

void UiObject::Refresh()
{
	// Implement in subclasses.
}

void UiObject::Tick()
{
	// Implement in subclasses.
}

std::string UiObject::GetName() const
{
	return Name;
}

std::string UiObject::GetInvisibleName() const
{
	// TODO: always remove "##" from the name if it exists,
	// then add "## to the beginning so the whole name is
	// guaranteed invisible
	if (Name.contains("##"))
	{
		return GetName();
	}
	else
	{
		return "##" + GetName();
	}
}

// TODO: add a "GetVisibleName()" function that
// that returns the full name without any "##" in it,
// guaranteeing that it is visible.