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
	std::string Str{};
	int X{ 0 };
	int Y{ 0 };
	bool XCentered{ false };
	Background Background{ Background::NONE };
	Foreground Foreground{ Foreground::NONE };
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

	int GetHeight() const { return this->_height; }
	int GetWidth() const { return this->_width; }
};

