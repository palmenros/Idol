#include "Window.h"
#include "Application.h"

namespace Idol
{

void Window::onWindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::onWindowKeyPress(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	Application::app->onKeyPress(key, scanCode, action, mods);
}

Window::Window(int width, int height, String name) : width(width), height(height), name(name), window(nullptr)
{
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(window);

}
bool Window::create()
{

	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if(!window)
	{
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, &Window::onWindowResize);
	
	glfwSetKeyCallback(window, &Window::onWindowKeyPress);

	int frameWidth, frameHeight;
	
	glfwGetFramebufferSize(window, &frameWidth, &frameHeight);
	glViewport(0, 0, frameWidth, frameHeight);

	return true;
}

void Window::destroy()
{
	glfwDestroyWindow(window);
}

void Window::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

}
