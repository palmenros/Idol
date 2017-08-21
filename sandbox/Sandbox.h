#pragma once
#include "id/app/Application.h"
#include "Idol.h"
#include <corecrt_math_defines.h>

using namespace Idol;

class Sandbox : public Idol::Application
{
public:

	GLuint vbo, vao, ebo;
	Shader* shader;
	Texture *container, *face;

	float alpha = 0;

	void render(double currentTime) override
	{
		shader->use();
		shader->setFloat("alpha", alpha);
		
		container->bind(0);
		face->bind(1);
	
		math::mat4 transform;		
		transform = math::translate(transform, math::vec3(0.5, -0.5, 0));
		transform = math::rotate(transform, math::radians(float(currentTime) * 40.f), math::vec3(0.f, 0.f, 1.f));
		transform = math::scale(transform, math::vec3(0.4, 0.4, 1));

		shader->setMat4("transform", transform);


		GLfloat black[] = { 0.f, 0.f, 0.f, 1.f };

		glClearBufferfv(GL_COLOR, 0, black);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


		math::mat4 secondTransform;
		
		float size = sinf(currentTime) * 0.5 + 0.5;
		size *= 0.7;

		secondTransform = math::translate(secondTransform, math::vec3(-0.5, 0.5, 0));
		secondTransform = math::scale(secondTransform, math::vec3(size, size, 1));
		shader->setMat4("transform", secondTransform);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}


	void setup() override
	{
		shader = Shader::createFromFile("//shaders/Shader.vert", "//shaders/Shader.frag");
		shader->compile();

		container = Texture::createFromFile("//textures/container.jpg");
		face = Texture::createFromFile("//textures/awesomeface.png");

		shader->use();
		shader->setInt("container", 0);
		shader->setInt("face", 1);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		GLfloat vertices[] =
		{
			//position (x, y) color(r, g, b) texture coordinates (x, y)
			-0.5f, -0.5f, 1.f, 0.f, 0.f, 0.f, 0.f, //bottom left
			0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f, //bottom right
			-0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f, //top left
			0.5f, 0.5f, 1.f, 1.f, 0.f, 1.f, 1.f //top right
		};

		uint indices[] =
		{
			0, 1, 2,
			1, 2, 3
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Set up attributes
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)(2 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)(5 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void cleanup() override
	{
		delete shader;
		delete face;
		delete container;
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void onKeyPress(int key, int scanCode, int action, int mods) override
	{
		if(key == GLFW_KEY_UP)
		{
			alpha += 0.01;
			if(alpha > 1)
			{
				alpha = 1;
			}
		}
		
		if(key == GLFW_KEY_DOWN)
		{
			alpha -= 0.01;
			if(alpha < 0)
			{
				alpha = 0;
			}
		}
	}

};
