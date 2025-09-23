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
	if (Name.contains("##"))
	{
		return GetName();
	}
	else
	{
		return "##" + GetName();
	}
}