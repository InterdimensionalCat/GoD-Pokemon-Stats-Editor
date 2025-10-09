#include "include.h"
#include "Editors/PokemonStats/BaseStatTotal.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleText.h"
#include "UI/UiElement/UiSimpleElement/IntElement/SimpleIntBox.h"

BaseStatTotal::BaseStatTotal(
	const std::string& InName,
	UiSection* InParent
) :
	UiSingleLineMultiElement(std::format("{}-MultiLine", InName), InParent)
{
	// Show simple text on the left as a label
	StatNameText = std::make_shared<SimpleText>(InName, InParent);

	// Show an IntBox that displays the stat total
	auto StatIntBoxName = std::format("##{}-IntBox", InName);
	TotalIntBox = std::make_shared<SimpleIntBox>(StatIntBoxName, InParent, 0, 0);

	TotalIntBox->SetElementMinSize(3);
	TotalIntBox->SetIsFixedSize(true);

	TotalIntBox->SetBounds(0, 999);

	AddElement(StatNameText);
	AddElement(TotalIntBox);
}

void BaseStatTotal::UpdateStatTotal(int32_t NewStatTotal)
{
	TotalIntBox->SetIntBuffer(static_cast<int>(NewStatTotal));
}

std::shared_ptr<SimpleIntBox> BaseStatTotal::GetIntBox()
{
	return TotalIntBox;
}
