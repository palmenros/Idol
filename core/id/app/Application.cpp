#include "Application.h"
#include "id/OpenGL.h"
#include "id/Common.h"

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

	if (glfwInit() != GLFW_TRUE)
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
	if (err != GLEW_OK)
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
	if (!initGLFW())
	{
		return false;
	}

	if (!window.create())
	{
		glfwTerminate();
		return false;
	}

	if (!initGLEW())
	{
		glfwTerminate();
		return false;
	}

	return true;
}

void Application::run()
{
	if (!init())
	{
#if DEBUG
		std::cin.get();
#endif
		return;
	}

	setup();

	while (!window.shouldClose())
	{
		render(glfwGetTime());
		window.update();
		checkErrors();
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

void Application::onKeyPress(int key, int scanCode, int action, int mods)
{
}

void Application::setMouseCoordinates(double xpos, double ypos)
{

	math::vec2 mouseCoordinates(xpos, ypos);

	if (firstMouse)
	{
		lastMouse = mouseCoordinates;
		firstMouse = false;
		return;
	}

	onMouseMoved(mouseCoordinates - lastMouse);
	lastMouse = mouseCoordinates;
}

int Application::getKey(int key)
{
	return window.getKey(key);
}

Application::Application() : window(800, 600, "OpenGL Lab")
{
	app = this;
}

void Application::checkErrors()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		ERROR(String("\nOpenGL error: ") + std::to_string(error) + ", " + getErrorString(error));
	}
}

String Application::getErrorString(GLenum error)
{
	switch (error)
	{
	case GL_INVALID_ENUM:
		return String("GL_INVALID_ENUM");
	case GL_INVALID_VALUE:
		return String("GL_INVALID_VALUE");
	case GL_INVALID_OPERATION:
		return String("GL_INVALID_OPERATION");
	case GL_STACK_OVERFLOW:
		return String("GL_STACK_OVERFLOW");
	case GL_STACK_UNDERFLOW:
		return String("GL_STACK_UNDERFLOW");
	case GL_OUT_OF_MEMORY:
		return String("GL_OUT_OF_MEMORY");
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return String("GL_INVALID_FRAMEBUFFER_OPERATION");
	case GL_CONTEXT_LOST:
		return String("GL_CONTEXT_LOST");
	case GL_TABLE_TOO_LARGE:
		return String("GL_TABLE_TOO_LARGE");
	default:
		return String("UNKNOWN_ERROR");
	}
}
}
