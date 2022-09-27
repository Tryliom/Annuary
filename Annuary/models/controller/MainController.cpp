#include "MainController.h"

#include <ranges>

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
	if (this->_view != nullptr)
	{
		this->_view->Update(this, this->_screen);
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
		std::string contact = "There is no contacts with this name";
		if (_contacts.contains(_name))
		{
			contact = _contacts[_name];
		}

		_screen.Draw(Text{ .str = "Search a contact", .x = _screen.GetWidth() / 2, .y = 2, .xCentered = true });
		_screen.Draw(Text{ .str = "Name:", .x = _screen.GetWidth() / 4, .y = 5 });
		_screen.Draw(Field{ .text = _name, .x = _screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = true });
		_screen.Draw(Text{ .str = contact, .x = _screen.GetWidth() / 2, .y = 7, .xCentered = true});

		_screen.Draw(Text{ .str = "Back: Esc", .x = _screen.GetWidth() / 2, .y = _screen.GetHeight() - 3, .xCentered = true });
	}
}

void MainController::onKeyPressed(const char key)
{
	if (_currentScreen == ScreenType::SEARCH_CONTACT)
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
		if (_views.empty())
		{
			exit(0);
		}

		GoBack();
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
