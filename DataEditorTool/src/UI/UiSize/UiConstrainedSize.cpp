#include "include.h"
#include "UI/UiSize/UiConstrainedSize.h"
#include "UI/UiSize/UiSize.h"

UiConstrainedSize::UiConstrainedSize()
	: ConstrainedSize(std::numeric_limits<float>::max())
{

}

UiConstrainedSize::UiConstrainedSize(const float InConstrainedSize)
	: ConstrainedSize(InConstrainedSize)
{

}

void UiConstrainedSize::CalculateFromSizeConstraints(
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

	// SizeConstraints do not account for label size, as this value will
	// be used for ImGui::PushItemWidth, which does not include the label size.
	const float MinSize = SizeConstraints->GetMinWithoutLabel();
	const float MaxSize = SizeConstraints->GetMaxWithoutLabel();
	const float LabelSizeWithSpacing = SizeConstraints->GetLabelSizeWithSpacing();
	const float SpaceWithNoLabel = SpaceAvailable - LabelSizeWithSpacing;

	// Default to the min size available, never go lower than this.
	ConstrainedSize = MinSize;

	// If the constraints are invalid (Min is greater than Max), 
	// fall back to a fixed size equal to the min, but log a warning.
	if (MinSize > MaxSize)
	{
		ICLogger::Warn(
			"UiConstrainedSize CalculateFromSizeConstraints was given invalid size constraints (MinSize:{} > MaxSize:{}). Falling back to MinSize.",
			MinSize, MaxSize);
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
	if (SpaceWithNoLabel > ConstrainedSize)
	{
		ConstrainedSize = std::min(MaxSize, SpaceWithNoLabel);
	}
}

void UiConstrainedSize::SetConstrainedSize(const float InConstrainedSize)
{
	ConstrainedSize = InConstrainedSize;
}

float UiConstrainedSize::GetConstrainedSize() const
{
	return ConstrainedSize;
}