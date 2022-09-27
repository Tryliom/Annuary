#pragma once
#include "../controller/Controller.h"
#include "../view/screen.h"

class Controller;

class View
{
public:
	virtual void Update(Controller* controller, Screen &screen) = 0;
	virtual void OnKeyPressed(Controller* controller, char key) = 0;
};

