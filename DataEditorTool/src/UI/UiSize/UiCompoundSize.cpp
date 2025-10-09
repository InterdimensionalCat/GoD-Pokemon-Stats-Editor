#include "include.h"
#include "UI/UiSize/UiCompoundSize.h"

UiCompoundSize::UiCompoundSize() : UiSize()
{
	
}

UiCompoundSize::UiCompoundSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider)
: UiSize()
{
	for (const auto& SizeToConsider : InSizesToConsider)
	{
		AddSizeToConsider(SizeToConsider);
	}
}

void UiCompoundSize::AddSizeToConsider(const std::shared_ptr<const UiSize>& SizeToConsider)
{
	SizesToConsider.push_back(SizeToConsider);
}

void UiCompoundSize::RemoveSizeToConsider(const std::shared_ptr<const UiSize>& SizeToConsider)
{
	SizesToConsider.erase(
		std::remove(SizesToConsider.begin(), SizesToConsider.end(), SizeToConsider),
		SizesToConsider.end()
	);
}

void UiCompoundSize::ClearSizesToConsider()
{
	SizesToConsider.clear();
}