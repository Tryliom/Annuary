#pragma once
#include "../view/Screen.h"

class Controller
{
protected:
	Screen _screen;
	bool _canPressKey{ true };

	/**
	 * \brief Used to draw things on the screen before rendering
	 */
	virtual void update() {}
	/**
	 * \brief Called when a key is pressed
	 * \param key The key pressed
	 */
	virtual void onKeyPressed(char key) {}
private:
	/**
	 * \brief Refresh screen rendering
	 */
	void refresh();
	/**
	 * \brief Start a thread to update the screen
	 */
	void startRenderingThread();
public:
	/**
	 * \brief Start the controller
	 */
	void Start();
};

