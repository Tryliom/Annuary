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
			auto next_frame = std::chrono::steady_clock::now();

			while (true)
			{
				next_frame += std::chrono::milliseconds(1000 / FPS);

				this->refresh();
				Tick++;
				if (LIMIT_FPS)
				{
					std::this_thread::sleep_until(next_frame);
				}
			}
		});
	t.detach();

	std::thread fpsThread([this]()
		{
			while (true)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				this->CurrentFPS = Tick;
				Tick = 0;
			}
		});
	fpsThread.detach();
}

void Controller::Start()
{
	startRenderingThread();
	while (const char key = static_cast<char>(_getch())) 
	{
		if (_canPressKey) {
			_canPressKey = false;
			this->onKeyPressed(key);
			_canPressKey = true;
		}
	}
}
