#include "ContactsView.h"
#include "../../controller/MainController.h"

#include <ranges>
#include <map>

void ContactsView::Update(Controller* controller, Screen& screen)
{
	// Get all contacts from the Main Controller
	auto contacts = dynamic_cast<MainController*>(controller)->GetContacts();
	// Draw the title of the view
	screen.Draw(Text{ .text = "Contacts", .x = screen.GetWidth() / 2, .y = 2, .xCentered = true });

	// Display every contacts
	int y = 5;
	for (const auto& key : contacts | std::views::keys)
	{
		screen.Draw(Text{ .text = key, .x = screen.GetWidth() / 4, .y = y });
		screen.Draw(Text{ .text = contacts[key], .x = screen.GetWidth() / 2, .y = y });
		y++;
	}
	// Display controls for the user
	screen.Draw(Text{ .text = "Back: Esc", .x = screen.GetWidth() / 2, .y = screen.GetHeight() - 3, .xCentered = true });
}
