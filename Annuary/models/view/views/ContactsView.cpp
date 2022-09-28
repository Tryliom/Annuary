#include "ContactsView.h"
#include "../../controller/MainController.h"

#include <ranges>
#include <map>

void ContactsView::Update(Controller* controller, Screen& screen)
{
	// Get all contacts from the Main Controller
	auto contacts = dynamic_cast<MainController*>(controller)->GetContacts();
	// Draw the title of the view
	screen.Draw(Text{ .Text = "Contacts", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });

	// Display every contacts
	int y = 5;
	for (const auto& key : contacts | std::views::keys)
	{
		screen.Draw(Text{ .Text = key, .X = screen.GetWidth() / 4, .Y = y });
		screen.Draw(Text{ .Text = contacts[key], .X = screen.GetWidth() / 2, .Y = y });
		y++;
	}
	// Display controls for the user
	screen.Draw(Text{ .Text = "Back: Esc", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
}
