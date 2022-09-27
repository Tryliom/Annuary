#include "SearchView.h"
#include "../../controller/MainController.h"

#include <map>

void SearchView::Update(Controller* controller, Screen& screen)
{
	screen.Draw(Text{ .str = "Search a contact", .x = screen.GetWidth() / 2, .y = 2, .xCentered = true });
	screen.Draw(Text{ .str = "Name:", .x = screen.GetWidth() / 4, .y = 5 });
	screen.Draw(Field{ .text = _name, .x = screen.GetWidth() / 4 + 6 + 3, .y = 5, .selected = true });
	screen.Draw(Text{ .str = _message, .x = screen.GetWidth() / 2, .y = 7, .xCentered = true });

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
	else if (key < 127 && key > 19)
	{
		_name += key;
	}

	if (contacts.contains(_name))
	{
		_message = "Number found: " + contacts[_name];
	}
	else
	{
		_message = "There is no contacts with this name";
	}
}
