#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class ComboBox;

class CSVIntHexComboBox : public UiBasicCSVElement<std::string>
{

public:

	CSVIntHexComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	CSVIntHexComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	virtual void Refresh() override;

	virtual void UiComponentUpdated() override;

	uint32_t GetSelectedEntry() const;

private:

	void UpdateEntriesList();

	std::shared_ptr<ComboBox> ComboBoxComponent;

	std::string EntriesListCSVFileName;

	std::string EntriesListColumnName;
};
