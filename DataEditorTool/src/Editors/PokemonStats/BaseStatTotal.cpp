#include "include.h"
#include "Editors/PokemonStats/BaseStatTotal.h"
#include "UI/BasicUiElements/SimpleText.h"
#include "UI/BasicUiElements/IntBox.h"

BaseStatTotal::BaseStatTotal(
	const std::string& InName,
	UiSection* InParent
) :
	MultiLineUiElement(std::format("{}-MultiLine", InName), InParent)
{
	// Show simple text on the left as a label
	StatNameText = std::make_shared<SimpleText>(InName, InParent);

	// Show an IntBox that displays the stat total
	auto StatIntBoxName = std::format("##{}-IntBox", InName);
	TotalIntBox = std::make_shared<IntBox>(StatIntBoxName, InParent, 0, 0);

	TotalIntBox->SetElementMinSize(3);
	TotalIntBox->GetSize().SetSizeRule(UiSizeRule_FixedSize);

	TotalIntBox->SetBounds(0, 999);

	AddElement(StatNameText);
	AddElement(TotalIntBox);
}

void BaseStatTotal::UpdateStatTotal(int32_t NewStatTotal)
{
	TotalIntBox->SetIntBuffer(static_cast<int>(NewStatTotal));
}

std::shared_ptr<IntBox> BaseStatTotal::GetIntBox()
{
	return TotalIntBox;
}
