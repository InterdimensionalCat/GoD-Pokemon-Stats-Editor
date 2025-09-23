#pragma once
//#include <string>
//#include <vector>
//#include <memory>

class OldUiSection;

bool FilterableComboBox(std::shared_ptr<OldUiSection> CurrentSection, const std::string& ComboBoxName, std::vector<std::string> UnfilteredItemsList, std::shared_ptr<std::string> SelectedItemString, std::shared_ptr<std::string> FilterString);