#pragma once
#include <string>
#include <vector>
#include <memory>

class UiSection;

bool FilterableComboBox(std::shared_ptr<UiSection> CurrentSection, const std::string& ComboBoxName, std::vector<std::string> UnfilteredItemsList, std::shared_ptr<std::string> SelectedItemString, std::shared_ptr<std::string> FilterString);