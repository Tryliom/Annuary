#include "Controller.h"

#include <conio.h>
#include <thread>

void Controller::refresh()
{
	_screen.Reset();
	this->update();
	_screen.Render();
}

void Controller::startRenderingThread()
{
	std::thread t([this]()
		{
			while (true)
			{
				this->refresh();
			}
		});
	t.detach();
}

void Controller::Start()
{
	while (const char key = static_cast<char>(_getch())) 
	{
		if (_canPressKey) {
			_canPressKey = false;
			this->onKeyPressed(key);
			_canPressKey = true;
		}
	}
}
