#pragma once
#include "id/app/Application.h"
#include "Idol.h"

using namespace Idol;

class Sandbox : public Idol::Application
{
public:

	VertexArray* vao = nullptr;
	Buffer* vbo;
	Shader* shader;
	Texture *container, *face;

	float deltaTime = 0, lastTime = 0;

	math::vec3 cameraPosition = math::vec3(0.f, 0.f, 4.f);
	math::vec3 cameraFront = math::vec3(0.f, 0.f, -1.f);
	math::vec3 cameraUp = math::vec3(0.f, 1.f, 0.f);

	float fov = 45, rot = 0;
	float far = 100, near = 0.1, aspectRatioModifier = 0.f;
	float yaw = 90, pitch = 0;

	Camera camera;

	glm::vec3 cubePositions[10] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

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

		container->bind(0);
		face->bind(1);

		math::mat4 view = camera.getViewMatrix();

		int height, width;
		window.getWindowSize(width, height);

		math::mat4 projection = math::perspective(math::radians(fov), float(width) / height, near, far);

		shader->setMat4("view", view);
		shader->setMat4("projection", projection);


		GLfloat black[] = {0.f, 0.f, 0.f, 1.f};

		glClear(GL_DEPTH_BUFFER_BIT);
		glClearBufferfv(GL_COLOR, 0, black);

		for (int i = 0; i < 10; i++)
		{
			const glm::vec3& v = cubePositions[i];
			math::mat4 model;
			model = math::translate(model, v);

			if (i % 3 == 0)
			{
				model = math::rotate(model, math::radians(rot), math::vec3(0.f, 1.f, 0.f));
			}

			shader->setMat4("model", model);
			vao->draw(36);
		}

		processInput();
	}


	void setup() override
	{
		glEnable(GL_DEPTH_TEST);

		shader = Shader::createFromFile("//shaders/Shader.vert", "//shaders/Shader.frag");
		shader->compile();

		container = Texture::createFromFile("//textures/container.jpg");
		face = Texture::createFromFile("//textures/awesomeface.png");

		shader->use();
		shader->setInt("container", 0);
		shader->setInt("face", 1);

		float vertices[] = {
			//Position (x, y, z)  TexCoord(x, y)
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		};

		vao = new VertexArray();

		BufferLayout layout;
		layout.pushElement(BufferElement(0, 3, GL_FLOAT));
		layout.pushElement(BufferElement(1, 2, GL_FLOAT));

		vbo = new Buffer(layout);
		vbo->setData(vertices, sizeof(vertices));

		vao->bind();
		vao->push(vbo);
		vao->setLayout();
	}

	void cleanup() override
	{
		delete shader;
		delete face;
		delete container;
		delete vao;
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
