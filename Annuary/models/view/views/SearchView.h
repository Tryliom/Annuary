#pragma once
#include "../View.h"

class SearchView: public View
{
private:
	std::string _name;
	std::string _message;

public:
	void Update(Controller* controller, Screen& screen) override;
	void OnKeyPressed(Controller* controller, char key) override;
};

