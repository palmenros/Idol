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
	virtual void render(double currentTime);

	/*
	 * Setup method, called on run.
	 * Only called once, with a valid OpenGL context
	 */
	virtual void setup();

	/*
	 * Cleanup the application
	 */
	virtual void cleanup();
};

}

