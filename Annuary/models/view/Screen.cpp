#include "screen.h"

#include <codecvt>
#include <iostream>
#include <thread>
#include <windows.h>

bool constexpr BORDER = true;
std::string const BORDER_COLUMN = "|";
std::string const BORDER_ROW = "=";

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
	this->_cache = {};
}

void Screen::Reset()
{
	// Set the height and width according to the console window
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(output, &csbi);
	this->_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	this->_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	this->_cache = this->_screen;
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
				if (h == 0 || h == _height - 1)
				{
					row.emplace_back(BORDER_ROW);
				}
				else if (w == 0 || w == _width - 1)
				{
					row.emplace_back(BORDER_COLUMN);
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

	// Reset cursor position
	_cursorX = -1;
	_cursorY = -1;
}

void Screen::Render() const
{
	// Display every lines of the screen
	for (int h = 0; h < _height; h++)
	{
		int w = 0;
		for (const auto& c : this->_screen[h])
		{
			if (static_cast<int>(this->_cache.size()) != _height || static_cast<int>(this->_cache[h].size()) != _width || this->_cache[h][w] != c)
			{
				this->setPos(w, h);
				std::cout << c;
			}
			w++;
		}
	}

	if (_cursorX != -1 && _cursorY != -1)
	{
		// Show the cursor
		const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(output, &cursorInfo);
		cursorInfo.bVisible = true;
		SetConsoleCursorInfo(output, &cursorInfo);
		this->setPos(_cursorX, _cursorY);
	}
}

void Screen::Draw(Text text)
{
	if (text.xCentered)
	{
		text.x -= static_cast<int>(text.text.length()) / 2;
	}

	// If the text is out of the screen, don't draw it
	if (_height <= text.y || _width <= text.x)
	{
		return;
	}

	// Colorize the text if a background or foreground color is specified
	std::string preColor, postColor;

	if (text.background != Background::NONE || text.foreground != Foreground::NONE)
	{
		std::string colors;
		preColor = "\033[";
		postColor = "\033[0m";

		if (text.background != Background::NONE)
		{
			colors += std::to_string(static_cast<int>(text.background));
		}
		if (text.foreground != Foreground::NONE)
		{
			if (!colors.empty())
			{
				colors += ";";
			}
			colors += std::to_string(static_cast<int>(text.foreground));
		}

		preColor += colors + "m";
	}

	for (int i = 0; i < static_cast<int>(text.text.size()); i++)
	{
		if (text.x + i >= _width)
		{
			break;
		}

		this->_screen[text.y][text.x + i] = preColor + text.text[i] + postColor;
	}
}

void Screen::Draw(const Button button)
{
	Background background = Background::NONE;
	Foreground foreground = Foreground::NONE;
	int x = button.x;

	if (button.xCentered)
	{
		x -= static_cast<int>(button.text.length()) / 2;
	}

	int y = button.y;

	if (button.yCentered)
	{
		y -= 1;
	}

	std::string border;

	for (int i = 0; i < static_cast<int>(button.text.length()) + 2; i++)
	{
		border += BORDER_ROW;
	}

	if (button.selected)
	{
		background = Background::CYAN;
		foreground = Foreground::BLACK;
	}

	this->Draw(Text{ .text = border, .x = x, .y = y, .background = background, .foreground = foreground });
	this->Draw(Text{ .text = BORDER_COLUMN + button.text + BORDER_COLUMN, .x = x, .y = y + 1, .background = background, .foreground = foreground });
	this->Draw(Text{ .text = border, .x = x, .y = y + 2, .background = background, .foreground = foreground });
}

void Screen::Draw(const Field& field)
{
	if (field.selected)
	{
		Draw(Text{ .text = field.text, .x = field.x, .y = field.y, .xCentered = field.xCentered, .background = Background::WHITE, .foreground = Foreground::BLACK });
		_cursorX = field.x + field.text.length();
		_cursorY = field.y;
	}
	else
	{
		Draw(Text{ .text = field.text, .x = field.x, .y = field.y, .xCentered = field.xCentered });
	}
}
