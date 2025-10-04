#pragma once
#include "UI/UiElement/UiCSVElement/UiCSVElement.h"

class ListBox;

class CSVRowSelector : public UiCSVElement
{


public:

	CSVRowSelector
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);


	virtual void Refresh() override;

	virtual void UiComponentUpdated() override;

	uint32_t GetSelectedEntry() const;

private:

	void UpdateEntriesList();

	std::shared_ptr<ListBox> ListBoxComponent;

};
