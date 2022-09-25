#pragma once
#include "Controller.h"
#include "../view/Screen.h"

#include <map>

enum class ScreenType
{
	MAIN,
	CONTACTS,
	CONTACT,
	EDIT_CONTACT,
	NEW_CONTACT,
	SEARCH_CONTACT,
	EXIT
};

class MainController final : public Controller
{
private:
	std::map<std::string, std::string> _contacts;
	std::string _currentContact;
	ScreenType _currentScreen;
	int _currentButton{-1};
	int _maxButtons{0};

	void updateScreenType(ScreenType screenType);
	void update() override;
	void onKeyPressed(char key) override;
public:
	MainController();

	void AddContact(const std::string& name, const std::string& number);
	std::string GetContact(const std::string& name);
};

