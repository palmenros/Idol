#include "Application.h"

namespace Idol
{

Application* Application::app = nullptr;

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
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if DEBUG
	LOG(String("\nGLFW version ") + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision) + " initialized succesfully");
#endif

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

#if DEBUG
	LOG("\nGLEW initialized:");
	LOG(String("VENDOR: ") + (GLchar*) glGetString(GL_VENDOR));
	LOG(String("VERSION: ") + (GLchar*) glGetString(GL_VERSION));
	LOG(String("RENDERER: ") + (GLchar*) glGetString(GL_RENDERER));
#endif

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
#if DEBUG
		std::cin.get();
#endif
		return;
	}

	setup();

	while(!window.shouldClose())
	{
		render(glfwGetTime());
		window.update();
	}

	cleanup();
	destroy();
}


void Application::destroy()
{
	window.destroy();
	glfwTerminate();
	app = nullptr;
}

Application::Application() : window(800, 600, "OpenGL Lab")
{
	app = this;
}

}