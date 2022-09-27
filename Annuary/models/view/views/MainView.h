#pragma once
#include "../View.h"

class MainView: public View
{
private:
	int _currentButton{ 0 };
	int _maxButtons{ 3 };

public:
	void Update(Controller* controller, Screen& screen) override;
	void OnKeyPressed(Controller* controller, char key) override;
};

