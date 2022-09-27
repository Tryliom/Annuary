#include "ContactsView.h"
#include "../../controller/MainController.h"

#include <ranges>
#include <map>

void ContactsView::Update(Controller* controller, Screen& screen)
{
	std::map<std::string, std::string> contacts = dynamic_cast<MainController*>(controller)->GetContacts();
	screen.Draw(Text{ .str = "Contacts", .x = screen.GetWidth() / 2, .y = 2, .xCentered = true });

	// Display every contacts
	int y = 5;
	for (const auto& key : contacts | std::views::keys)
	{
		screen.Draw(Text{ .str = key, .x = screen.GetWidth() / 4, .y = y });
		screen.Draw(Text{ .str = contacts[key], .x = screen.GetWidth() / 2, .y = y });
		y++;
	}

	screen.Draw(Text{ .str = "Back: Esc", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
}
