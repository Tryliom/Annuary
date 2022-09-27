#include "MainView.h"

#include "ContactsView.h"
#include "NewContactView.h"
#include "SearchView.h"
#include "../../controller/MainController.h"


void MainView::Update(Controller* controller, Screen& screen)
{
	screen.Draw(Text{ .str = "Directory", .x = screen.GetWidth() / 2, .y = 2, .xCentered = true });

	screen.Draw(Button{ .text = "New contact", .x = screen.GetWidth() / 4, .y = 5, .selected = _currentButton == 0, .xCentered = true });
	screen.Draw(Button{ .text = "Search a contact", .x = screen.GetWidth() / 2, .y = 5, .selected = _currentButton == 1, .xCentered = true });
	screen.Draw(Button{ .text = "Display contacts", .x = screen.GetWidth() * 3 / 4, .y = 5, .selected = _currentButton == 2, .xCentered = true });

	screen.Draw(Text{ .str = "Exit: Esc | Arrows: move | Confirm: Enter", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
}

void MainView::OnKeyPressed(Controller* controller, const char key)
{
	if (key == KEY_LEFT)
	{
		_currentButton--;
	}
	else if (key == KEY_RIGHT)
	{
		_currentButton++;
	}
	else if (key == KEY_ENTER)
	{
		if (_currentButton == 0)
		{
			dynamic_cast<MainController*>(controller)->ChangeView(new NewContactView());
		}
		else if (_currentButton == 1)
		{
			dynamic_cast<MainController*>(controller)->ChangeView(new SearchView());
		}
		else if (_currentButton == 2)
		{
			dynamic_cast<MainController*>(controller)->ChangeView(new ContactsView());
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
}
