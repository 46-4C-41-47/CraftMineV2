#include "../include/Camera.h"


Camera::Camera() 
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	computeVectors();

	viewMatrix = glm::mat4(1.0f);
	rebuildViewMatrix();
	proccessMouse(0, 0);
}


Camera::Camera(glm::vec3 pos, glm::vec3 pointToLook)
{
	position = pos;
	vectors.direction = glm::normalize(pos - pointToLook);
	computeVectors();
	
	viewMatrix = glm::mat4(1.0f);
	rebuildViewMatrix();
	proccessMouse(0, 0);
}


Camera::~Camera() {}


void Camera::computeVectors() 
{
	vectors.up = glm::vec3(0.0f, 1.0f, 0.0f);
	vectors.right = glm::normalize(glm::cross(vectors.up, vectors.direction));
	vectors.up = glm::cross(vectors.direction, vectors.right);
}

void Camera::rebuildViewMatrix() 
{
	viewMatrix = glm::lookAt(position, position + (-vectors.direction), vectors.up);
}


void Camera::move(glm::vec3 newLocation) 
{
	position = newLocation;
	rebuildViewMatrix();
}


void Camera::computeDirection() 
{
	vectors.direction.x = glm::cos(yawValue) * glm::cos(pitchValue);
	vectors.direction.y = glm::sin(pitchValue);
	vectors.direction.z = glm::sin(yawValue) * glm::cos(pitchValue);

	computeVectors();
	rebuildViewMatrix();
}


void Camera::moveUpward(float offset) 
{
	position = position + glm::vec3(0.0f, offset, 0.0f);
	rebuildViewMatrix();
}

void Camera::moveSideWays(float offset) 
{
	position = position + glm::vec3(
		vectors.right.x * offset,
		vectors.right.y * offset,
		vectors.right.z * offset
	);
	rebuildViewMatrix();
}

void Camera::moveForward(float offset) 
{
	glm::vec3 normalizedDirection = glm::normalize(glm::vec3(
		vectors.direction.x, 
		0, 
		vectors.direction.z
	));

	position = position - glm::vec3(
		normalizedDirection.x * offset,
		0, 
		normalizedDirection.z * offset
	);
	rebuildViewMatrix();
}


void Camera::yaw(float angleInRadians) 
{ 
	yawValue += angleInRadians; 
	computeDirection();
}

void Camera::pitch(float angleInRadians) 
{ 
	pitchValue += angleInRadians;
	
	double halfPI = PI * 0.5;

	if (pitchValue > halfPI)
		pitchValue = halfPI;

	if (pitchValue < -halfPI)
		pitchValue = -halfPI;

	computeDirection();
}


void Camera::proccessMouse(int x, int y) 
{
	if (lastX == -1 || lastY == -1) {
		lastX = x;
		lastY = y;
	}

	yaw((x - lastX) * params::controls::HORIZONTAL_SENSITIVITY);
	pitch((y - lastY) * params::controls::VERTICAL_SENSITIVITY);

	lastX = x;
	lastY = y;
}


float Camera::getYaw() const { return yawValue; }


float Camera::getPitch() const { return pitchValue; }


float Camera::getRoll() const { return rollValue; }


CameraVectors Camera::getVectors() const { return vectors; }


glm::mat4 Camera::getViewMatrix() const { return viewMatrix; }


glm::vec3 Camera::getPosition() const { return position; }
