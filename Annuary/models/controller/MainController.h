#pragma once
#include "Controller.h"
#include "../view/Screen.h"

#include <map>

enum class ScreenType
{
	MAIN,
	CONTACTS,
	NEW_CONTACT,
	SEARCH_CONTACT
};

class MainController final : public Controller
{
private:
	std::map<std::string, std::string> _contacts;
	ScreenType _currentScreen;
	int _currentButton{-1};
	int _maxButtons{0};
	std::string _name;
	std::string _number;

	void updateScreenType(ScreenType screenType);
	void update() override;
	void onKeyPressed(char key) override;
public:
	MainController();

	void AddContact(const std::string& name, const std::string& number);
	std::string GetContact(const std::string& name);
};

