#include "NewContactView.h"
#include "../../controller/MainController.h"

void NewContactView::Update(Controller* controller, Screen& screen)
{
	screen.Draw(Text{ .str = "Name:", .x = screen.GetWidth() / 4, .y = 5 });
	screen.Draw(Field{ .text = _name, .x = screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = _currentButton == 0 });
	screen.Draw(Text{ .str = "Phone number:", .x = screen.GetWidth() / 4, .y = 7 });
	screen.Draw(Field{ .text = _number, .x = screen.GetWidth() / 4 + 13 + 3, .y = 7, .selected = _currentButton == 1 });
	screen.Draw(Button{ .text = "Save", .x = screen.GetWidth() / 2, .y = 9, .selected = _currentButton == 2, .xCentered = true });

	screen.Draw(Text{ .str = "Back: Esc | Arrows: move | Confirm: Enter", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
}

void NewContactView::OnKeyPressed(Controller* controller, const char key)
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
			dynamic_cast<MainController*>(controller)->AddContact(_name, _number);
			dynamic_cast<MainController*>(controller)->GoBack();
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
