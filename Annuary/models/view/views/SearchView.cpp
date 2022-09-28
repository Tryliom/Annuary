#include "SearchView.h"
#include "../../controller/MainController.h"

#include <map>

void SearchView::Update(Controller* controller, Screen& screen)
{
	// Draw the title of the view
	screen.Draw(Text{ .Str = "Search a contact", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });
	// Draw the name field
	screen.Draw(Text{ .Str = "Name:", .X = screen.GetWidth() / 4, .Y = 5 });
	screen.Draw(Field{ .Str = _name, .X = screen.GetWidth() / 4 + 6 + 3, .Y = 5, .Selected = true });
	// Display the search results
	screen.Draw(Text{ .Str = _message, .X = screen.GetWidth() / 2, .Y = 7, .XCentered = true });
	// Display controls for the user
	screen.Draw(Text{ .Str = "Back: Esc", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
}

void SearchView::OnKeyPressed(Controller* controller, const char key)
{
	std::map<std::string, std::string> contacts = dynamic_cast<MainController*>(controller)->GetContacts();

	if (key == KEY_BACKSPACE)
	{
		if (!_name.empty())
		{
			_name.pop_back();
		}
	}
	// Limit the characters used to be a-z, A-Z or space
	else if (key <= 90 && key >= 65 || key <= 122 && key >= 97 || key == 32)
	{
		_name += key;
	}

	// Update message to display the search results
	if (contacts.contains(_name))
	{
		_message = "Number found: " + contacts[_name];
	}
	else
	{
		_message = "There is no contacts with this name";
	}
}
