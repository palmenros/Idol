#pragma once

#include "Idol.h"

namespace Idol
{

class Window
{
private:
	int height;
	int width;
	String name;
	GLFWwindow* window;

public:
	
	static void onWindowResize(GLFWwindow* window, int width, int height);

	Window(int width, int height, String name);

	/*
	 * Return if the window should close in next frame
	 */
	bool shouldClose() const;

	/*
	 * Create window
	 * Returns true if success or false if fail
	 */
	bool create();

	/*
	 * Cleanup window
	 */
	void destroy();

	/*
	 * Called every tick to update window
	 */
	void update();
};

}


