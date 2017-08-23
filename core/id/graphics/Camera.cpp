#include "Camera.h"

namespace Idol{

Camera::Camera(math::vec3 position, const math::vec3& worldUp, float pitch, float yaw, float speed, float sensitivity)
	: position(position), worldUp(worldUp), pitch(pitch), yaw(yaw), sensitivity(sensitivity), speed(speed)
{
	recalculateVectors();
}

math::mat4 Camera::getViewMatrix() const
{
	return math::lookAt(position, position + getForwardVector(), worldUp);
}

math::vec3 Camera::getForwardVector() const
{
	return forwardVector;
}

math::vec3 Camera::getRightVector() const
{
	return rightVector;
}

math::vec3 Camera::getUpVector() const
{
	return upVector;
}

void Camera::onMouseMoved(const math::vec2& offset, bool constrainPitch)
{

	//Reverse both axis
	pitch -= offset.y * sensitivity;
	yaw -= offset.x * sensitivity;

	//Normalize pitch and yaw
	if(constrainPitch)
	{	
		//Limit pitch to (-90, 90)

		if(pitch > 89.9)
		{
			pitch = 89.9;
		}

		if(pitch < -89.9)
		{
			pitch = -89.9;
		}
	}
	else
	{
		pitch = std::fmod(pitch, 360.f);
	}

	yaw = std::fmod(yaw, 360.f);

	recalculateVectors();

}

void Camera::move(ECameraDirection direction, float deltaTime)
{

	math::vec3 velocity(0.f);

	switch(direction)
	{
	case ECameraDirection::Forwards:
		velocity += getForwardVector();
		break;
	case ECameraDirection::Backwards:
		velocity -= getForwardVector();
		break;
	case ECameraDirection::Right:
		velocity += getRightVector();
		break;
	case ECameraDirection::Left:
		velocity -= getRightVector();
		break;
	case ECameraDirection::Up:
		velocity += getUpVector();
		break;
	case ECameraDirection::Down:
		velocity -= getUpVector();
		break;
	default: ;
	}

	if(velocity != math::vec3(0.f))
	{
		position += math::normalize(velocity) * speed * deltaTime;
	}

}

void Camera::recalculateVectors()
{
	forwardVector.x = cos(math::radians(yaw)) * cos(math::radians(pitch));
	forwardVector.y = sin(math::radians(pitch));
	forwardVector.z = -sin(math::radians(yaw)) * cos(math::radians(pitch));

	rightVector = math::normalize(math::cross(forwardVector, worldUp));
	upVector = math::normalize(math::cross(forwardVector, - rightVector));

}
}
