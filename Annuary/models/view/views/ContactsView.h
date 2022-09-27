#pragma once
#include "../View.h"

class ContactsView: public View
{
public:
	void Update(Controller* controller, Screen& screen) override;
	void OnKeyPressed(Controller* controller, char key) override {};
};

