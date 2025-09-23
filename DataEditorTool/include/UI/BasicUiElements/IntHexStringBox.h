#include "UI/BasicUiElements/BasicUiElement.h"
#include "imgui/imgui.h"

class IntHexStringBox : public BasicUiElement<std::string>
{
public:

	IntHexStringBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	IntHexStringBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	virtual void Refresh() override;

	virtual void Tick() override;
	
	/**
	 * Set this element's min required size by passing in the 
	 * number of digits this should be able to show. 
	 * Will factor in step counter size if enabled.
	 */
	void SetElementMinSize(const uint32_t MinNumDigits);

	/**
	 * Set this element's max required size by passing in the 
	 * number of digits this should be able to show. 
	 * Will factor in step counter size if enabled.
	 */
	void SetElementMaxSize(const uint32_t MaxNumDigits);

	/** Set the Min/Max value bounds. */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	int GetMinValue() const;
	int GetMaxValue() const;

private:

	void SetManagedValueFromBuffer();

	const int StepSize;

	const int FastStepSize;

	int MinValue;

	int MaxValue;

	int IntBuffer = -1;

};
