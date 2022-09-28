#include "MainView.h"

#include "ContactsView.h"
#include "NewContactView.h"
#include "SearchView.h"
#include "../../controller/MainController.h"


void MainView::Update(Controller* controller, Screen& screen)
{
	// Draw the title of the view
	screen.Draw(Text{ .str = "Directory", .x = screen.GetWidth() / 2, .y = 2, .xCentered = true });
	// Draw the menu buttons
	screen.Draw(Button{ .text = "New contact", .x = screen.GetWidth() / 4, .y = 5, .selected = _currentButton == 0, .xCentered = true });
	screen.Draw(Button{ .text = "Search a contact", .x = screen.GetWidth() / 2, .y = 5, .selected = _currentButton == 1, .xCentered = true });
	screen.Draw(Button{ .text = "Display contacts", .x = screen.GetWidth() * 3 / 4, .y = 5, .selected = _currentButton == 2, .xCentered = true });
	// Display controls for the user
	screen.Draw(Text{ .str = "Exit: Esc | Arrows: move | Confirm: Enter", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
}

void MainView::OnKeyPressed(Controller* controller, const char key)
{
	// Change the selected field/button with left/right arrows
	if (key == KEY_LEFT)
	{
		_currentButton--;
	}
	else if (key == KEY_RIGHT)
	{
		_currentButton++;
	}
	// If the user press enter, got to the selected view
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
