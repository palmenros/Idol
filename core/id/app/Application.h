#pragma once

#include "id/app/Window.h"
#include "id/Math.h"

namespace Idol
{

class Application
{
protected:

	/*
	* Application's window instance
	*/
	Window window;

private:

	bool firstMouse = true;

	/*
	 * Init GLFW
	 */
	bool initGLFW();

	/*
	 * Init GLEW
	 */
	bool initGLEW();

	/*
	 * Init OpenGL, GLFW and GLEW
	 * Returns true if init is successful
	 */
	bool init();
	
	/*
	 * Function called by GLFW when error happens
	 */
	static void errorCallback(int errorCode, const char* description);

	void checkErrors();

	String getErrorString(GLenum error);

	math::vec2 lastMouse;

public:
	static Application* app;

	/*
	 * Virtual destructor
	 */
	virtual ~Application() = default;

	/*
	 * Start the application
	 */
	void run();

	/**
	 * Default constructor
	 */
	Application();

	/*
	 * Called every frame
	 * @param currentTime Time since the start of the Application
	 */
	virtual void render(double currentTime) = 0;

	/*
	 * Setup method, called on run.
	 * Only called once, with a valid OpenGL context
	 */
	virtual void setup() = 0;

	/*
	 * Cleanup the application
	 */
	virtual void cleanup() = 0;

	/*
	 * Delete window and OpenGL context
	 */
	void destroy();

	virtual void onKeyPress(int key, int scanCode, int action, int mods);
	void setMouseCoordinates(double xpos, double ypos);

	virtual void onMouseMoved(const math::vec2& offset) = 0;

	int getKey(int key);
};

}

