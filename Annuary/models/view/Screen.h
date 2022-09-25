#pragma once

#include <string>
#include <vector>


enum class Foreground
{
	NONE,
	BLACK = 30,
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	MAGENTA = 35,
	CYAN = 36,
	WHITE = 37,
};

enum class Background
{
	NONE,
	BLACK = 40,
	RED = 41,
	GREEN = 42,
	YELLOW = 43,
	BLUE = 44,
	MAGENTA = 45,
	CYAN = 46,
	WHITE = 47,
};

struct Text
{
	std::string str{};
	int x{ 0 };
	int y{ 0 };
	bool xCentered{ false };
	Background background{ Background::NONE };
	Foreground foreground{ Foreground::NONE };
};

struct Button
{
	std::string text{};
	int x{ 0 };
	int y{ 0 };
	bool selected{ false };
	bool xCentered{ false };
	bool yCentered{ false };
};

class Screen
{
private:
	std::vector<std::vector<std::string>> _screen;
	int _height;
	int _width;

	static void setPos(int x, int y);
public:
	Screen();

	void Reset();

	void Render() const;

	void Draw(Text text);

	void Draw(Button button);

	int GetHeight() const { return this->_height; }
	int GetWidth() const { return this->_width; }
};

