#pragma once

#include "id/OpenGL.h"
#include "id/Types.h"

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
	static void onWindowKeyPress(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

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

	void getWindowSize(int& width, int& height);
	int getKey(int key);
};

}


