#include "ItemSizeUtils.h"

std::pair<float, std::string> GetMaxTextSize(const std::map<std::string, std::string>& Container)
{
	float CurrentMax = -1;
	std::string CurrentMaxElement = "";
	for (auto It = Container.begin(); It != Container.end(); It++)
	{
		std::string Element = (std::string)It->first;
		float ElementLength = ImGui::CalcTextSize(Element.c_str(), 0, true).x;
		if (ElementLength > CurrentMax)
		{
			CurrentMax = ElementLength;
			CurrentMaxElement = Element;
			std::cout << std::format("New Max found: {} with length {}", CurrentMaxElement, CurrentMax) << "\n";
		}
	}

	std::cout << std::format("Overall max: {} with length {}", CurrentMaxElement, CurrentMax) << "\n";

	return std::pair<float, std::string>(CurrentMax, CurrentMaxElement);
}
