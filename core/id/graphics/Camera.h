#pragma once

#include "id/Math.h"

namespace Idol
{

enum class ECameraDirection
{
	Forwards,
	Backwards,
	Right,
	Left,
	Up,
	Down
};

class Camera
{
protected:

	math::vec3 forwardVector;
	math::vec3 rightVector;
	math::vec3 upVector;

public:

	math::vec3 position;
	math::vec3 worldUp;

	float pitch;
	float yaw;

	float sensitivity;
	float speed;

	Camera(math::vec3 position, const math::vec3& worldUp = math::vec3(0.f, 1.f, 0.f), float pitch = 0.f, float yaw = 90.f, float speed = 5.f, float sensitivity = 0.2f);

	math::mat4 getViewMatrix() const;

	math::vec3 getForwardVector() const;
	math::vec3 getRightVector() const;
	math::vec3 getUpVector() const;

	void onMouseMoved(const math::vec2& offset, bool constrainPitch = true);
	void move(ECameraDirection direction, float deltaTime);
	
	void recalculateVectors();

};

}


