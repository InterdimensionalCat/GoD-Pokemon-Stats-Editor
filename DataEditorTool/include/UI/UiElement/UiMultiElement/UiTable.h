/*****************************************************************//**
 * \file   UiTable.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiTable : public UiMultiElement
{

public:

	UiTable(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	void AddNewColumn(const std::string& ColumnName);

	void SetRowFilter(const std::string& FilterString);

	void SetColumnFilter(const std::string& FilterString);

private:

	std::shared_ptr<UiSize> TableSize;

	std::vector<std::string> ColumnNames;

	std::vector<std::vector<std::shared_ptr<UiElement>>> TableColumns;

	ImGuiTextFilter RowFilter;

	ImGuiTextFilter ColumnFilter;
};
