#include "screen.h"

#include <codecvt>
#include <iostream>
#include <thread>
#include <windows.h>

bool constexpr BORDER = true;

void Screen::setPos(const int x, const int y)
{
	// Set the position of the cursor
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

Screen::Screen()
{
	this->_height = 0;
	this->_width = 0;
	this->_screen = {};
}

void Screen::Reset()
{
	// Set the height and width according to the console window
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(output, &csbi);
	this->_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	this->_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	this->_screen = {};

	// Hide the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(output, &cursorInfo);

	// Fill the screen with spaces and # if BORDER is true for borders
	for (int h = 0; h < _height; h++)
	{
		std::vector<std::string> row;
		for (int w = 0; w < _width; w++)
		{
			if (BORDER)
			{
				if (w == 0 || w == _width - 1 || h == 0 || h == _height - 1)
				{
					row.emplace_back("#");
				}
				else
				{
					row.emplace_back(" ");
				}
			}
			else
			{
				row.emplace_back(" ");
			}
		}

		this->_screen.emplace_back(row);
	}
}

void Screen::Render() const
{
	// Display every lines of the screen
	for (int h = 0; h < _height; h++)
	{
		this->setPos(0, h);
		for (const auto& c : this->_screen[h])
		{
			std::cout << c;
		}
	}
}

void Screen::Draw(Text text)
{
	if (text.XCentered)
	{
		text.X -= static_cast<int>(text.Str.length()) / 2;
	}

	// If the text is out of the screen, don't draw it
	if (_height <= text.Y || _width <= text.X)
	{
		return;
	}

	// Colorize the text if a background or foreground color is specified
	std::string preColor, postColor;

	if (text.Background != Background::NONE || text.Foreground != Foreground::NONE)
	{
		std::string colors;
		preColor = "\033[";
		postColor = "\033[0m";

		if (text.Background != Background::NONE)
		{
			colors += std::to_string(static_cast<int>(text.Background));
		}
		if (text.Foreground != Foreground::NONE)
		{
			if (!colors.empty())
			{
				colors += ";";
			}
			colors += std::to_string(static_cast<int>(text.Foreground));
		}

		preColor += colors + "m";
	}

	for (int i = 0; i < static_cast<int>(text.Str.size()); i++)
	{
		if (text.X + i >= _width)
		{
			break;
		}

		this->_screen[text.Y][text.X + i] = preColor + text.Str[i] + postColor;
	}
}
