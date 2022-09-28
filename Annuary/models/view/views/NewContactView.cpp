#include "NewContactView.h"
#include "../../controller/MainController.h"
#include "../../utilities/StringUtility.h"

void NewContactView::Update(Controller* controller, Screen& screen)
{
	// Draw name field
	screen.Draw(Text{ .text = "Name:", .x = screen.GetWidth() / 4, .y = 5 });
	screen.Draw(Field{ .text = _name, .x = screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = _currentButton == 0 });
	// Draw phone number field
	screen.Draw(Text{ .text = "Phone number:", .x = screen.GetWidth() / 4, .y = 7 });
	screen.Draw(Field{ .text = _number, .x = screen.GetWidth() / 4 + 13 + 3, .y = 7, .selected = _currentButton == 1 });
	// Draw save button
	screen.Draw(Button{ .text = "Save", .x = screen.GetWidth() / 2, .y = 9, .selected = _currentButton == 2, .xCentered = true });
	// Draw the error message if there is any
	screen.Draw(Text{ .text = _errorMessage, .x = screen.GetWidth() / 2, .y = screen.GetHeight() / 2, .xCentered = true, .background = Background::RED, .foreground = Foreground::WHITE });
	// Display controls for the user
	screen.Draw(Text{ .text = "Back: Esc | Arrows: move | Confirm: Enter", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
}

void NewContactView::OnKeyPressed(Controller* controller, const char key)
{
	// Clear the error message every time the user press a key
	_errorMessage.clear();

	// Change the selected field/button with up/down arrows
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
		// Save the new contact if on save, otherwise switch to next button
		if (_currentButton == _maxButtons - 1)
		{
			// Trim fields
			_name = StringUtility::trim(_name);
			_number = StringUtility::trim(_number);

			// If one of the fields are empty, display an error message
			if (_name.empty())
			{
				_errorMessage = "The name is empty !";
			}
			else if (_number.empty())
			{
				_errorMessage = "The phone number is empty !";
			}
			else
			{
				// Add the new contact to the contacts
				const auto mainController = dynamic_cast<MainController*>(controller);
				mainController->AddContact(_name, _number);
				mainController->GoBack();
			}
		}
		else
		{
			_currentButton++;
		}
	}
	else if (key == KEY_BACKSPACE)
	{
		// Remove a character from the selected field if he's not empty
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
			// Limit the characters used to be a-z, A-Z or space
			if (key <= 90 && key >= 65 || key <= 122 && key >= 97 || key == 32)
			{
				// Limit the length to 60 characters maximum
				if (_name.length() < 60)
				{
					_name += key;
				} else
				{
					_errorMessage = "Max length of name is 60 characters";
				}
			}
		}
		else if (_currentButton == 1)
		{
			// Limit the characters used to be 0-9, + or space
			if (key >= 48 && key <= 57 || key == 43 || key == 32)
			{
				// Limit the length to 40 characters maximum
				if (_number.length() < 40)
				{
					_number += key;
				} else
				{
					_errorMessage = "Max length of phone number is 40 characters";
				}
			}
		}
	}
	// Correct the current button if it's out of bounds
	if (_currentButton >= _maxButtons)
	{
		_currentButton = _maxButtons - 1;
	}
	if (_currentButton < 0)
	{
		_currentButton = 0;
	}
}
