#pragma once
#include "../view/Screen.h"

class Controller
{
private:
	Screen _screen;
	bool _canPressKey{ true };
	/**
	 * \brief Refresh screen rendering
	 */
	void refresh();
	/**
	 * \brief Start a thread to update the screen
	 */
	void startRenderingThread();
	/**
	 * \brief Used to draw things on the screen before rendering
	 */
	virtual void update() {}
	/**
	 * \brief Called when a key is pressed
	 * \param key The key pressed
	 */
	virtual void onKeyPressed(char key) {}
public:
	virtual ~Controller() = default;
	/**
	 * \brief Start the controller
	 */
	void Start();
};

