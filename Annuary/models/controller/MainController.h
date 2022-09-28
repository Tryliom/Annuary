#pragma once
#include "Controller.h"
#include "../view/Screen.h"

#include <map>

class MainController final : public Controller
{
private:
	// The list of contacts
	std::map<std::string, std::string> _contacts;
	
	void update() override;
	void onKeyPressed(char key) override;
public:
	MainController();
	/**
	 * \brief Add a contact to the list
	 * \param name The name of the contact
	 * \param number The number of the contact
	 */
	void AddContact(const std::string& name, const std::string& number);
	/**
	 * \brief Get the list of contacts
	 * \return The list of contacts
	 */
	std::map<std::string, std::string> GetContacts() const { return _contacts; }
};

