#include "include.h"
#include "UI/UiSize/UiConstrainedSizeWithLabel.h"
#include "UI/UiSize/UiSize.h"

UiConstrainedSizeWithLabel::UiConstrainedSizeWithLabel() : UiConstrainedSize()
{

}

UiConstrainedSizeWithLabel::UiConstrainedSizeWithLabel(const float InConstrainedSize) :
	UiConstrainedSize(InConstrainedSize)
{

}

void UiConstrainedSizeWithLabel::CalculateFromSizeConstraints(
	const float SpaceAvailable,
	const std::shared_ptr<const UiSize> SizeConstraints
)
{
	if (SizeConstraints == nullptr)
	{
		// If no size constraints are given, just use
		// the available space, but log a warning as
		// SetConstrainedSize should be used instead.
		ICLogger::Warn(
			"UiConstrainedSize CalculateFromSizeConstraints was given a null SizeConstraints. Falling back to using all available space: {}",
			SpaceAvailable);

		ConstrainedSize = SpaceAvailable;
		return;
	}

	// This particular UiConstrainedSize does include the label in its size calculations.
	const float MinSize = SizeConstraints->GetMinWithLabel();
	const float MaxSize = SizeConstraints->GetMaxWithLabel();

	// Default to the min size available, never go lower than this.
	ConstrainedSize = MinSize;

	// If the constraints are invalid (Min is greater than Max), 
	// fall back to a fixed size equal to the min, but log a warning.
	if (MinSize > MaxSize)
	{
		//ICLogger::Warn(
		//	"UiConstrainedSizeWithLabel CalculateFromSizeConstraints was given invalid size constraints (MinSize:{} > MaxSize:{}). Falling back to MinSize.",
		//	MinSize, MaxSize);
		return;
	}

	// If this is a fixed size, then we always use the min size.
	if (SizeConstraints->IsFixedSize())
	{
		return;
	}

	// If we have more space than the min available, set the element size to the
	// max space available, leaving room for the label, or the max size, whichever
	// is smaller.
	if (SpaceAvailable > ConstrainedSize)
	{
		ConstrainedSize = std::min(MaxSize, SpaceAvailable);
	}
}