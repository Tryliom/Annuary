#pragma once
#include "../View.h"

class NewContactView: public View
{
private:
	int _currentButton{ 0 };
	int _maxButtons{ 3 };
	std::string _name;
	std::string _number;
	std::string _errorMessage;

public:
	void Update(Controller* controller, Screen& screen) override;
	void OnKeyPressed(Controller* controller, char key) override;
};

