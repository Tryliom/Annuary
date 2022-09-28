#include "MainController.h"
#include "../view/views/MainView.h"

#include <ranges>
#include <thread>

MainController::MainController() : Controller()
{
	ChangeView(new MainView());
}

void MainController::update()
{
	if (this->_view != nullptr)
	{
		this->_view->Update(this, this->_screen);
	} else
	{
		_screen.Draw(Text{ .Text = "Annuary has been exited", .X = _screen.GetWidth() / 2, .Y = 3, .XCentered = true });
	}
}

void MainController::onKeyPressed(const char key)
{
	if (this->_view != nullptr)
	{
		this->_view->OnKeyPressed(this, key);
	}

	if (key == KEY_ESC)
	{
		if (_views.empty())
		{
			// Close the program
			this->_view = nullptr;
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			exit(0);
		}

		GoBack();
	}
}

void MainController::AddContact(const std::string& name, const std::string& number)
{
	_contacts[name] = number;
}
