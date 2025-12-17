#include "include.h"
#include "Editors/Trainers/TrainersEditorTrainersList.h"

#include "Editors/Trainers/TrainersEditor.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVRowSelector.h"

TrainersEditorTrainersList::TrainersEditorTrainersList(TrainersEditor* InParent) : UiSection("Trainers List", InParent)
{
	std::shared_ptr<CSVRowSelector> PokemonEntrySelector = std::make_shared<CSVRowSelector>("##Trainers Entry List", this, InParent->GetTrainerCSVFileName(), "Entry Name");

	AddElement(PokemonEntrySelector);
}