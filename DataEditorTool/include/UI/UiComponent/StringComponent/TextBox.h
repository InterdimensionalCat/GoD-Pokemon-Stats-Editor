#pragma once
#include "UI/UiComponent/UiComponent.h"

class TextBox : public UiComponent
{

public:

	TextBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	virtual void DisplayComponent() override;

	virtual float CalculateInternalSpace() const override;

	void SetTextBoxBuffer(const std::string& NewBufferValue);

	std::string GetTextBoxBuffer() const;

private:

	std::string TextBoxBuffer = "---";
};