#pragma once
#include "Controller.h"
#include "../view/Screen.h"

#include <map>

class MainController final : public Controller
{
private:
	std::map<std::string, std::string> _contacts;
	
	void update() override;
	void onKeyPressed(char key) override;
public:
	MainController();

	void AddContact(const std::string& name, const std::string& number);
	std::map<std::string, std::string> GetContacts() const { return _contacts; }
};

