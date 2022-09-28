#include "MainView.h"

#include "ContactsView.h"
#include "NewContactView.h"
#include "SearchView.h"
#include "../../controller/MainController.h"


void MainView::Update(Controller* controller, Screen& screen)
{
	// Draw the title of the view
	screen.Draw(Text{ .Text = "Directory", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });
	// Draw the menu buttons
	screen.Draw(Button{ .Str = "New contact", .X = screen.GetWidth() / 4, .Y = 5, .Selected = _currentButton == 0, .XCentered = true });
	screen.Draw(Button{ .Str = "Search a contact", .X = screen.GetWidth() / 2, .Y = 5, .Selected = _currentButton == 1, .XCentered = true });
	screen.Draw(Button{ .Str = "Display contacts", .X = screen.GetWidth() * 3 / 4, .Y = 5, .Selected = _currentButton == 2, .XCentered = true });
	// Display controls for the user
	screen.Draw(Text{ .Text = "Exit: Esc | Arrows: move | Confirm: Enter", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
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
