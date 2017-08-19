#pragma once
#include "id/app/Application.h"
#include <cmath>

class Sandbox : public Idol::Application
{
public:

	void render(double currentTime) override
	{
		GLfloat color[] = {
			sinf(currentTime) * 0.5 + 0.5,
			cosf(currentTime) * 0.5 + 0.5,
			sinf(currentTime + 2) * 0.5 + 0.5,
			1.f
		};

		glClearBufferfv(GL_COLOR, 0, color);

	}

	virtual void setup() override
	{
		
	}
};


