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

const std::string& UiObject::GetName() const
{
	return Name;
}

std::string UiObject::GetInvisibleName() const
{
	std::string InvisName = GetName();
	while (InvisName.contains("##"))
	{
		InvisName.erase(InvisName.find("##"), 2);
	}

	return "##" + InvisName;
}

// TODO: add a "GetVisibleName()" function that
// that returns the full name without any "##" in it,
// guaranteeing that it is visible.