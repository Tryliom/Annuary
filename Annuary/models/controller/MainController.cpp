#include "MainController.h"

#include <ranges>

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;
constexpr auto KEY_ENTER = 13;
constexpr auto KEY_ESC = 27;
constexpr auto KEY_BACKSPACE = 8;

MainController::MainController() : Controller()
{
	updateScreenType(ScreenType::MAIN);
}

void MainController::updateScreenType(const ScreenType screenType)
{
	_currentScreen = screenType;
	_currentButton = 0;
	_name.clear();
	_number.clear();

	if (_currentScreen == ScreenType::MAIN)
	{
		_maxButtons = 3;
	}
	else if (_currentScreen == ScreenType::CONTACTS)
	{
		_maxButtons = 2;
	}
	else if (_currentScreen == ScreenType::NEW_CONTACT)
	{
		_maxButtons = 2;
	}
	else if (_currentScreen == ScreenType::SEARCH_CONTACT)
	{
		_maxButtons = 2;
	}
}

void MainController::update()
{
	if (_currentScreen == ScreenType::MAIN)
	{
		_screen.Draw(Text{ .str = "Directory", .x = _screen.GetWidth() / 2, .y = 2, .xCentered = true });

		_screen.Draw(Button{ .text = "New contact", .x = _screen.GetWidth() / 4, .y = 5, .selected = _currentButton == 0, .xCentered = true });
		_screen.Draw(Button{ .text = "Search a contact", .x = _screen.GetWidth() / 2, .y = 5, .selected = _currentButton == 1, .xCentered = true });
		_screen.Draw(Button{ .text = "Display contacts", .x = _screen.GetWidth() * 3 / 4, .y = 5, .selected = _currentButton == 2, .xCentered = true });

		_screen.Draw(Text{ .str = "Exit: Esc | Arrows: move | Confirm: Enter", .x = _screen.GetWidth() / 2, .y = _screen.GetHeight() - 3, .xCentered = true });
	}

	if (_currentScreen == ScreenType::NEW_CONTACT)
	{
		// Create fields
		_screen.Draw(Text{ .str = "Name:", .x = _screen.GetWidth() / 4, .y = 5 });
		_screen.Draw(Field{ .text = _name, .x = _screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = _currentButton == 0 });
		_screen.Draw(Text{ .str = "Phone number:", .x = _screen.GetWidth() / 4, .y = 7 });
		_screen.Draw(Field{ .text = _number, .x = _screen.GetWidth() / 4 + 13 + 3, .y = 7, .selected = _currentButton == 1 });
		_screen.Draw(Button{ .text = "Save", .x = _screen.GetWidth() / 2, .y = 9, .selected = _currentButton == 2, .xCentered = true });

		_screen.Draw(Text{ .str = "Back: Esc | Arrows: move | Confirm: Enter", .x = _screen.GetWidth() / 2, .y = _screen.GetHeight() - 3, .xCentered = true });
	}

	if (_currentScreen == ScreenType::CONTACTS)
	{
		_screen.Draw(Text{ .str = "Contacts", .x = _screen.GetWidth() / 2, .y = 2, .xCentered = true });

		// Display every contacts
		int y = 5;
		for (const auto& key : _contacts | std::views::keys)
		{
			_screen.Draw(Text{ .str = key, .x = _screen.GetWidth() / 4, .y = y });
			_screen.Draw(Text{ .str = _contacts[key], .x = _screen.GetWidth() / 2, .y = y});
			y++;
		}

		_screen.Draw(Text{ .str = "Back: Esc", .x = _screen.GetWidth() / 2, .y = _screen.GetHeight() - 3, .xCentered = true });
	}

	if (_currentScreen == ScreenType::SEARCH_CONTACT)
	{
		_screen.Draw(Text{ .str = "Search a contact", .x = _screen.GetWidth() / 2, .y = 2, .xCentered = true });
		
		_screen.Draw(Text{ .str = "Name:", .x = _screen.GetWidth() / 4, .y = 5 });
		_screen.Draw(Field{ .text = _name, .x = _screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = true });
		_screen.Draw(Text{ .str = _contacts.contains(_name) ? "Found a number: " + _contacts[_name] : "There is no contacts with this name", 
			.x = _screen.GetWidth() / 2, .y = 7, .xCentered = true});

		_screen.Draw(Text{ .str = "Back: Esc", .x = _screen.GetWidth() / 2, .y = _screen.GetHeight() - 3, .xCentered = true });
	}
}

void MainController::onKeyPressed(const char key)
{
	if (_currentScreen == ScreenType::MAIN)
	{
		switch (key)
		{
		case KEY_LEFT:
			_currentButton--;
			break;
		case KEY_RIGHT:
			_currentButton++;
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
				updateScreenType(ScreenType::CONTACTS);
				break;
			}
			break;
		default:
			break;
		}
	}
	else if (_currentScreen == ScreenType::NEW_CONTACT)
	{
		if (key == KEY_UP)
		{
			_currentButton--;
		}
		else if (key == KEY_DOWN)
		{
			_currentButton++;
		}
		else if (key == KEY_ENTER)
		{
			if (_currentButton == _maxButtons - 1)
			{
				AddContact(_name, _number);
				updateScreenType(ScreenType::MAIN);
			}
			else
			{
				_currentButton++;
			}
		}
		else if (key == KEY_BACKSPACE)
		{
			if (_currentButton == 0)
			{
				if (!_name.empty())
				{
					_name.pop_back();
				}
			}
			else if (_currentButton == 1)
			{
				if (!_number.empty())
				{
					_number.pop_back();
				}
			}
		}
		else
		{
			if (_currentButton == 0)
			{
				_name += key;
			}
			else if (_currentButton == 1)
			{
				_number += key;
			}
		}
	}
	else if (_currentScreen == ScreenType::SEARCH_CONTACT)
	{

		if (key == KEY_BACKSPACE)
		{
			if (_currentButton == 0)
			{
				if (!_name.empty())
				{
					_name.pop_back();
				}
			}
			else if (_currentButton == 1)
			{
				if (!_number.empty())
				{
					_number.pop_back();
				}
			}
		}
		else if (key < 127 && key > 19)
		{
			if (_currentButton == 0)
			{
				_name += key;
			}
			else if (_currentButton == 1)
			{
				_number += key;
			}
		}
	}

	if (_currentButton >= _maxButtons)
	{
		_currentButton = _maxButtons - 1;
	}
	if (_currentButton < 0)
	{
		_currentButton = 0;
	}

	if (key == KEY_ESC)
	{
		if (_currentScreen == ScreenType::MAIN)
		{
			exit(0);
		}

		updateScreenType(ScreenType::MAIN);
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
