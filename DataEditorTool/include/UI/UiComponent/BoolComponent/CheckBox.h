#pragma once
#include "UI/UiComponent/UiComponent.h"

class UiElement;
class UiSize;

class CheckBox : public UiComponent
{

public:

	CheckBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	virtual void DisplayComponent() override;

	virtual float CalculateInternalSpace() const override;

	void SetBoolBuffer(const bool InBufferVal);

	bool GetBoolBuffer() const;

private:

	bool bBoolBuffer = false;
};
