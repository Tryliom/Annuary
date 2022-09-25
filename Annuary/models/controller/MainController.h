#pragma once
#include "Controller.h"
#include "../view/Screen.h"

#include <map>

class MainController final : public Controller
{
private:
	std::map<std::string, std::string> _contacts;

	std::string _currentContact;

	void update() override;

	void onKeyPressed(char key) override;
public:
	MainController();

	void AddContact(std::string name, std::string number);

	std::string GetContact(std::string name);
};

