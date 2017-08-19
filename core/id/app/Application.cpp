#include "Application.h"

namespace Idol
{

void Application::errorCallback(int errorCode, const char* description)
{
	ERROR("GLFW ERROR: " + String(description));
}

bool Application::initGLFW()
{
	glfwSetErrorCallback(&Application::errorCallback);

	if(glfwInit() != GLFW_TRUE)
	{
		return false;
	}

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	LOG(String("GLFW version ") + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision) + " initialized succesfully");

	return true;
}

bool Application::initGLEW()
{
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		ERROR(String("GLEW ERROR: ") + (GLchar*)glewGetErrorString(err));
		return false;
	}

	LOG("GLEW initialized");

	return true;
}

bool Application::init()
{
	if(!initGLFW())
	{
		return false;
	}

	if(!window.create())
	{
		glfwTerminate();
		return false;
	}

	if(!initGLEW())
	{
		glfwTerminate();
		return false;
	}

	return true;
}

void Application::run()
{
	if(!init())
	{
		return;
	}

	setup();

	while(!window.shouldClose())
	{
		render(glfwGetTime());
		window.update();
	}

	cleanup();
}

void Application::cleanup()
{
	window.destroy();
	glfwTerminate();
}

Application::Application() : window(640, 480, "OpenGL Lab")
{
}

void Application::setup()
{
}

void Application::render(double currentTime)
{
}

}