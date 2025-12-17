#include "include.h"
#include "UI/UiSection.h"
#include "UI/UiElement/UiElement.h"
#include "UI/UiSize/UiSize.h"
#include "UI/UiSize/UiConstrainedSize.h"

UiElement::UiElement(const std::string& InName, UiSection* InParent) :
	UiObject(InName, InParent),
	ParentSection(InParent),
	ConstrainedSize(std::make_shared<UiConstrainedSize>()),
	bShouldOverrideSyncedSize(false)
{

}

void UiElement::CalculateConstrainedSize(const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize, const std::shared_ptr<const UiSize>& ParentSizeConstraints)
{

	auto SizeConstraints = GetSizeConstraints();

	if (ShouldOverrideSyncedSize() || SizeConstraints->IsFixedSize())
	{
		// Calculate the constrained size from our own size constraints 
		// if ShouldOverrideSyncedSize is set or if this is a fixed size element.
		// However, warn if this is a fixed size element but ShouldOverrideSyncedSize
		// is false, as this is likely a mistake.
		if (!ShouldOverrideSyncedSize() && SizeConstraints->IsFixedSize())
		{
			//ICLogger::Warn("UiElement {} has a fixed size but does not override synced size. This may be a mistake.", GetName());
		}

		// Always use the parent's constrained size as the space available.
		ConstrainedSize->CalculateFromSizeConstraints(
			ParentConstrainedSize->GetConstrainedSize(),
			GetSizeConstraints()
		);
	}
	else
	{
		// Otherwise calculate using the Parent's synced size.
		ConstrainedSize->CalculateFromSizeConstraints(
			ParentConstrainedSize->GetConstrainedSize(),
			ParentSizeConstraints
		);
	}
}

void UiElement::SetShouldOverrideSyncedSize(const bool bInShouldOverride)
{
	bShouldOverrideSyncedSize = bInShouldOverride;
}

bool UiElement::ShouldOverrideSyncedSize() const
{
	return bShouldOverrideSyncedSize;
}
