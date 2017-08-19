#include "Window.h"

namespace Idol
{

Window::Window(int width, int height, String name) : width(width), height(height), name(name)
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
