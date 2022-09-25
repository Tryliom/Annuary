#include "MainController.h"

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;
constexpr auto KEY_ENTER = 13;
constexpr auto KEY_ESC = 27;

MainController::MainController() : Controller()
{
	updateScreenType(ScreenType::MAIN);
}

void MainController::updateScreenType(const ScreenType screenType)
{
	_currentScreen = screenType;
	_currentButton = -1;
	switch (_currentScreen)
	{
		case ScreenType::MAIN:
			_maxButtons = 3;
			break;
		case ScreenType::CONTACTS:
			_maxButtons = 3;
			break;
	}
}

void MainController::update()
{
	if (_currentScreen == ScreenType::MAIN)
	{
		_screen.Draw(Text{ .str = "Directory", .x = _screen.GetWidth() / 2, .y = 2, .xCentered = true });

		if (_currentContact.empty())
		{
			// Draw buttons
			_screen.Draw(Button{ .text = "New contact", .x = _screen.GetWidth() / 3, .y = 5, .selected = _currentButton == 0, .xCentered = true });
			_screen.Draw(Button{ .text = "Search a contact", .x = _screen.GetWidth() / 2, .y = 5, .selected = _currentButton == 1, .xCentered = true });
			_screen.Draw(Button{ .text = "Exit", .x = _screen.GetWidth() * 2 / 3, .y = 5, .selected = _currentButton == 2, .xCentered = true });
		}
	}
}

void MainController::onKeyPressed(const char key)
{
	switch (_currentScreen)
	{
		case ScreenType::MAIN:
			switch (key)
			{
				case KEY_LEFT:
					_currentButton--;
					if (_currentButton < 0)
					{
						_currentButton = 0;
					}
					break;
				case KEY_RIGHT:
					_currentButton++;
					if (_currentButton >= _maxButtons)
					{
						_currentButton = _maxButtons - 1;
					}
					break;
				case KEY_ENTER:
					switch (_currentButton)
					{
						case 0:
							updateScreenType(ScreenType::NEW_CONTACT);
							break;
						case 1:
							updateScreenType(ScreenType::SEARCH_CONTACT);
							break;
						case 2:
							updateScreenType(ScreenType::EXIT);
							break;
					}
					break;
				default:
					break;
			}
			break;
	}
}

void MainController::AddContact(const std::string& name, const std::string& number)
{
	_contacts[name] = number;
}

std::string MainController::GetContact(const std::string& name)
{
	return _contacts[name];
}
