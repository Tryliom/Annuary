#include "NewContactView.h"
#include "../../controller/MainController.h"
#include "../../utilities/StringUtility.h"

void NewContactView::Update(Controller* controller, Screen& screen)
{
	screen.Draw(Text{ .str = "Name:", .x = screen.GetWidth() / 4, .y = 5 });
	screen.Draw(Field{ .text = _name, .x = screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = _currentButton == 0 });
	screen.Draw(Text{ .str = "Phone number:", .x = screen.GetWidth() / 4, .y = 7 });
	screen.Draw(Field{ .text = _number, .x = screen.GetWidth() / 4 + 13 + 3, .y = 7, .selected = _currentButton == 1 });
	screen.Draw(Button{ .text = "Save", .x = screen.GetWidth() / 2, .y = 9, .selected = _currentButton == 2, .xCentered = true });
	screen.Draw(Text{ .str = _errorMessage, .x = screen.GetWidth() / 2, .y = screen.GetHeight() / 2, .xCentered = true, .background = Background::RED, .foreground = Foreground::WHITE });

	screen.Draw(Text{ .str = "Back: Esc | Arrows: move | Confirm: Enter", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
}

void NewContactView::OnKeyPressed(Controller* controller, const char key)
{
	_errorMessage.clear();

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
			_name = StringUtility::trim(_name);
			_number = StringUtility::trim(_number);

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
			if (key <= 90 && key >= 65 || key <= 122 && key >= 97 || key == 32)
			{
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
			if (key >= 48 && key <= 57 || key == 43 || key == 32)
			{
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
}
