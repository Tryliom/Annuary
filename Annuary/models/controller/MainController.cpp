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
			_screen.Draw(Button{ .text = "New contact", .x = _screen.GetWidth() / 4, .y = 5, .selected = _currentButton == 0, .xCentered = true });
			_screen.Draw(Button{ .text = "Search a contact", .x = _screen.GetWidth() / 2, .y = 5, .selected = _currentButton == 1, .xCentered = true });
			_screen.Draw(Button{ .text = "Exit", .x = _screen.GetWidth() * 3 / 4, .y = 5, .selected = _currentButton == 2, .xCentered = true });
		}
	}

	if (_currentScreen == ScreenType::NEW_CONTACT)
	{
		// Create fields
	}

	if (_currentScreen == ScreenType::CONTACTS)
	{
		_screen.Draw(Text{ .str = "Contacts", .x = _screen.GetWidth() / 2, .y = 2, .xCentered = true });

		// Display every contacts
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
							exit(0);
					}
					break;
				default:
					break;
			}
			break;
		case ScreenType::CONTACTS:
			switch (key)
			{
			case KEY_UP:
				
				break;
			case KEY_DOWN:
				
				break;
			case KEY_ENTER:
				
				break;
			default:
				break;
			}
			break;
	}

	if (key == KEY_ESC)
	{
		if (_currentScreen == ScreenType::MAIN)
		{
			exit(0);
		}
		else
		{
			updateScreenType(ScreenType::MAIN);
		}
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
