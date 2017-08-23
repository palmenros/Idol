#pragma once
#include "id/app/Application.h"
#include "Idol.h"

using namespace Idol;

class Sandbox : public Idol::Application
{
public:

	VertexArray* vao = nullptr, *lampVao = nullptr;
	Buffer* vbo, *lampvbo;
	Shader* shader, *lampShader;

	float deltaTime = 0, lastTime = 0;

	float fov = 45.f;
	float far = 100, near = 0.1, aspectRatioModifier = 0.f;

	Camera camera;

	math::vec3 objectColor = math::vec3(1, 0.5, 0.31);
	math::vec3 lightColor = math::vec3(1, 1, 1);

	math::vec3 lightPosition = math::vec3(1.2, 1.f, 2.f);


	Sandbox() : camera(math::vec3(0.f, 0.f, 4.f))
	{
	}

	void onMouseMoved(const math::vec2& offset)
	{
		camera.onMouseMoved(offset);
	}

	void render(double currentTime) override
	{
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		
		shader->use();

		int height, width;
		window.getWindowSize(width, height);

		math::mat4 projection = math::perspective(math::radians(fov), float(width) / height, near, far);

		shader->setMat4("view", camera.getViewMatrix());
		shader->setMat4("projection", projection);
		
		math::mat4 model;
		model = math::rotate(model, (float)currentTime, math::vec3(0.f, 1.f, 0.f));
		shader->setMat4("model", model);

		GLfloat black[] = {0.f, 0.f, 0.f, 1.f};

		glClear(GL_DEPTH_BUFFER_BIT);
		glClearBufferfv(GL_COLOR, 0, black);

		shader->setVec3("objectColor", objectColor);
		shader->setVec3("lightColor", lightColor);
		shader->setVec3("lightPos", lightPosition);
	
		vao->draw(36);

		lampShader->use();
		lampShader->setMat4("view", camera.getViewMatrix());
		lampShader->setMat4("projection", projection);
		
		math::mat4 lampModel;
		lampModel = math::translate(lampModel, lightPosition);
		lampModel = math::scale(lampModel, math::vec3(0.2f));
		lampShader->setMat4("model", lampModel);
		
		lampVao->draw(36);

		processInput();
	}

	void setup() override
	{
		glEnable(GL_DEPTH_TEST);

		shader = Shader::createFromFile("//shaders/Shader.vert", "//shaders/Shader.frag");
		shader->compile();

		lampShader = Shader::createFromFile("//shaders/Lamp.vert", "//shaders/Lamp.frag");
		lampShader->compile();

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		vao = new VertexArray();

		BufferLayout layout;
		layout.pushElement(BufferElement(0, 3, GL_FLOAT));
		layout.pushElement(BufferElement(1, 3, GL_FLOAT));

		vbo = new Buffer(layout);
		vbo->setData(vertices, sizeof(vertices));

		vao->bind();
		vao->push(vbo);
		vao->setLayout();
	
		BufferLayout lampLayout;
		lampLayout.pushElement(BufferElement(0, 3, GL_FLOAT));
		lampLayout.pushElement(BufferElement(-1, 3, GL_FLOAT));


		lampvbo = new Buffer(lampLayout);
		lampvbo->setData(vertices, sizeof(vertices));

		lampVao = new VertexArray();
		lampVao->bind();
		lampVao->push(lampvbo);
		lampVao->setLayout();
	}

	void cleanup() override
	{
		delete shader;
		delete vao;
		delete lampVao;
	}

	void processInput()
	{

		if(getKey(GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.move(ECameraDirection::Forwards, deltaTime);
		}

		if (getKey(GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.move(ECameraDirection::Backwards, deltaTime);
		}

		if (getKey(GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.move(ECameraDirection::Right, deltaTime);
		}

		if (getKey(GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.move(ECameraDirection::Left, deltaTime);
		}

		if (getKey(GLFW_KEY_E) == GLFW_PRESS)
		{
			camera.move(ECameraDirection::Up, deltaTime);
		}

		if (getKey(GLFW_KEY_Q) == GLFW_PRESS)
		{
			camera.move(ECameraDirection::Down, deltaTime);
		}
	}
};
