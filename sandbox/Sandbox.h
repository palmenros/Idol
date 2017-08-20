#pragma once
#include "id/app/Application.h"
#include "Idol.h"

using namespace Idol;

class Sandbox : public Idol::Application
{
public:

	GLuint vbo;
	Shader* shader;

	GLuint vao;

	void render(double currentTime) override
	{
		shader->bind();
		
		float r = sin(currentTime) * 0.5 + 0.5;
		float g = cos(currentTime) * 0.5 + 0.5;
		float b = sin(currentTime + 2) * 0.5 + 0.5;

		shader->setUniform4f("color", math::vec4(r, g, b, 1));

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}


	void setup() override
	{
		shader = Shader::createFromFile("//shaders/Shader.vert", "//shaders/Shader.frag");
		shader->compile();

		GLfloat vertices[] =
		{
				-0.5, 0.5, 0,  //top left
				-0.5, -0.5, 0, //bottom left
				0.5, 0.5, 0,   //top right
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
	
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
	
	}

	void cleanup() override
	{
		delete shader;
	}
};


