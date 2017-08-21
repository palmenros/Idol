#pragma once
#include "Idol.h"
#include "id/app/Window.h"
namespace Idol
{

class Application
{
private:

	/*
	 * Application's window instance
	 */
	Window window;

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

	virtual void onKeyPress(int key, int scanCode, int action, int mods) = 0;

};

}

