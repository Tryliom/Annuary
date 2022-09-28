#include "SearchView.h"
#include "../../controller/MainController.h"

#include <map>

void SearchView::Update(Controller* controller, Screen& screen)
{
	// Draw the title of the view
	screen.Draw(Text{ .str = "Search a contact", .x = screen.GetWidth() / 2, .y = 2, .xCentered = true });
	// Draw the name field
	screen.Draw(Text{ .str = "Name:", .x = screen.GetWidth() / 4, .y = 5 });
	screen.Draw(Field{ .text = _name, .x = screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = true });
	// Display the search results
	screen.Draw(Text{ .str = _message, .x = screen.GetWidth() / 2, .y = 7, .xCentered = true });
	// Display controls for the user
	screen.Draw(Text{ .str = "Back: Esc", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
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
